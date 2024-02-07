
#include "SHA256-Cuda.cuh"
#include "computation.cuh"
#include "preprocessing.cuh"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sys/types.h>

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

  for (unsigned int i : hArr) {
    printf("hello");
    printf("%#010x", i);
  }

  printf("\n");

  free(paddedBits);
  free(bits);
  free(schedule);
}

int main() {
  string strArr[] = {"RedBlockBlue", "12345", "zorgLover123", "openSesame"};
  size_t bitsBytes = sizeof(uint8_t *) * size(strArr);
  size_t strSizesBytes = sizeof(int) * size(strArr);
  uint8_t **h_bits = (uint8_t **)malloc(bitsBytes);
  int *h_strSizes = (int *)malloc(strSizesBytes);
  uint8_t **d_bits;
  int *d_strSizes;
  int count = 0;

  for (int i = 0; i < size(strArr); i++) {
    h_bits[i] = string_to_binary(strArr[i]);
    h_strSizes[i] = size(strArr);
  }

  cudaMalloc(&d_bits, sizeof(uint8_t *) * size(strArr));
  cudaMalloc(&d_strSizes, sizeof(int) * size(strArr));

  cudaMemcpy(d_bits, h_bits, bitsBytes, cudaMemcpyHostToDevice);
  cudaMemcpy(d_strSizes, h_strSizes, strSizesBytes, cudaMemcpyHostToDevice);

  free(h_bits);
  free(h_strSizes);

  sha<<<1, 4>>>(d_bits, d_strSizes);
  cudaDeviceSynchronize();

  // solution for timer found on stack overflow
  /*auto now = std::chrono::steady_clock::now;
  duration<long> executeTime = 1s;
  auto start = now();

  while ((now() - start) < executeTime) {
    sha<<<1, 4>>>(bits, strSizes);
    count += 4;
  }*/

  cout << "Hashes per second: " << dec << count << endl;
  // sha(strArr[0]);
}
