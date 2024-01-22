//
// Created by ross on 27/10/23.
//
//

// upgraded implementation to no longer use bitset and use malloc to declare
// arrays. All arrays are now passed as pointers for efficiency

#include "SHA256-Cuda.cuh"
#include "computation.cuh"
#include "preprocessing.cuh"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iterator>

__global__ void sha(uint8_t **bitsArr, int *strSizes) {
  uint32_t *paddedBits;
  int threadID = threadIdx.x;
  uint8_t *bits = bitsArr[threadID];
  int strSize = strSizes[threadID];

  uint32_t hArr[] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                     0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

  paddedBits = pad_binary(bits, strSize);

  add_length_bits(paddedBits, (strSize * 8));

  uint32_t *schedule;

  schedule = prepare_message_schedule(paddedBits);

  compute_hash(schedule, hArr);

  printf("hash: ");

  for (uint32_t h : hArr) {
    printf("%#010x\n", h);
  }

  free(paddedBits);
  free(bits);
  free(schedule);
}

int main() {
  string strArr[] = {"RedBlockBlue", "12345", "zorgLover123", "openSesame"};
  uint8_t **bits = (uint8_t **)malloc(sizeof(uint8_t *) * size(strArr));
  int *strSizes = (int *)malloc(sizeof(int) * size(strArr));
  int count = 0;

  for (int i = 0; i < size(strArr); i++) {
    bits[i] = string_to_binary(strArr[i]);
    strSizes[i] = size(strArr);
  }

  sha<<<1, 4>>>(bits, strSizes);

  // solution for timer found on stack overflow
  /*auto now = std::chrono::steady_clock::now;
  duration<long> executeTime = 1s;
  auto start = now();

  while ((now() - start) < executeTime) {
    sha<<<1, 4>>>(bits, strSizes);
    count += 4;
  }*/

  free(bits);
  free(strSizes);

  cout << "Hashes per second: " << dec << count << endl;
  // sha(strArr[0]);
}
