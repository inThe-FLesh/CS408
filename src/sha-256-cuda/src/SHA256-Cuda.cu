
#include "SHA256-Cuda.cuh"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <strings.h>
#include <sys/types.h>


#include "SHA256-Cuda.cuh"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sys/types.h>
#define gpuErrchk(ans)                                                         \
  { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line,
                      bool abort = true) {
  if (code != cudaSuccess) {
    fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file,
            line);
    if (abort)
      exit(code);
  }
}

/*I had to move all of the functions from the other files
  into this file, otherwise it wouldn't build correctly*/

__global__ void sha(cudaStrArr *charArr, int *strSizes, uint32_t *hArr) {
  uint32_t *paddedBits;
  int threadID = threadIdx.x;
  int strSize = strSizes[threadID];
  char* testStr = charArr->strArr;
  int* testPosition = charArr->positions;

  char *str = getString(charArr->strArr, charArr->positions, threadID);

  uint8_t *bits = string_to_binary(str, strSize);

  paddedBits = pad_binary(bits, strSize);

  /*if (threadID == 0) {
    printf("padded bits: ");

    for (int i = 0; i < 16; i++) {
      printf("%x ", paddedBits[i]);
    }
  }*/

  add_length_bits(paddedBits, (strSize * 8));

  uint32_t *schedule;

  schedule = prepare_message_schedule(paddedBits);

  compute_hash(schedule, hArr);

  if (threadID == 0) {

    printf("hash: ");

    for (int i = 0; i < 8; i++) {
      printf("%x", hArr[i]);
    }

    printf("\n");
  }

  free(paddedBits);
  free(bits);
  free(schedule);
}

int main() {
  string strArr[] = {"RedBlockBlue", "12345", "zorgLover123", "openSesame"};
  cudaStrArr *h_charArr = (cudaStrArr *)malloc(sizeof(cudaStrArr));

  h_charArr->strArr = createCharArr(strArr, size(strArr));

  h_charArr->positions = getPositions(strArr, size(strArr));

  size_t strSizesBytes = sizeof(char) * 12;
  size_t hArrSizeBytes = sizeof(uint32_t) * 8;

  int *h_strSizes = (int *)malloc(strSizesBytes);

  uint32_t hArr[] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                     0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

  cudaStrArr *d_charArr;
  int *d_strSizes;
  uint32_t *d_hArr;

  int count = 0;

  for (int i = 0; i < 4; i++) {
    h_strSizes[i] = 12;
  }

  cudaMalloc(&d_charArr, sizeof(cudaStrArr));
  cudaMalloc(&d_strSizes, strSizesBytes);
  cudaMalloc(&d_hArr, hArrSizeBytes);

  cudaMemcpy(d_charArr, h_charArr, sizeof(cudaStrArr), cudaMemcpyHostToDevice);
  cudaMemcpy(d_strSizes, h_strSizes, strSizesBytes, cudaMemcpyHostToDevice);
  cudaMemcpy(d_hArr, hArr, hArrSizeBytes, cudaMemcpyHostToDevice);

  sha<<<1, 4>>>(d_charArr, d_strSizes, d_hArr);

  cudaMemcpy(hArr, d_hArr, hArrSizeBytes, cudaMemcpyDeviceToHost);
  gpuErrchk(cudaPeekAtLastError());

  // solution for timer found on stack overflow
  /*auto now = std::chrono::steady_clock::now;
  duration<long> executeTime = 1s;
  auto start = now();

  while ((now() - start) < executeTime) {
    sha<<<1, 4>>>(bits, strSizes);
    count += 4;
  }*/

  // cout << "Hashes per second: " << dec << count << endl;
}

__host__ char *createCharArr(string *strArr, int strArrSize) {
  string output;

  for (int i = 0; i < strArrSize; i++) {
    output += strArr[i];
  }

  char *outputChar = (char *)malloc(sizeof(char) * (output.length() + 1));
  strcpy(outputChar, output.c_str());

  return outputChar;
}

__host__ int *getPositions(string *strArr, int strArrSize) {
  int *positions = (int *)malloc(sizeof(int) * (strArrSize * 2));

  positions[0] = 0;
  positions[1] = strArr[0].length();

  for (int i = 1; i < strArrSize; i++) {
    positions[i + 1] = strArr[i].length();
  }

  return positions;
}

__device__ char *getString(char *str, int *positions, int index) {
  int position = positions[index];
  int length = (positions[index + 1] - position);
  char *outputStr = (char *)malloc(sizeof(char) * length);

  for (int i = position, j = 0; i < length; i++, j++) {
    // using i and j here as the output string has to start at 0
    // and str has to start from position
    outputStr[j] = str[i];
  }
  return outputStr;
}

/*Preprocessing code*/

// Convert the string into binary representation. 8 bits per character.
__device__ uint8_t *string_to_binary(const char *str, const int strLen) {
  // breaks up each word in the string to an 8-bit binary number and adds them
  // to  the array.
  uint8_t *bits = (uint8_t *)malloc(sizeof(uint8_t) * strLen);

  for (int i = 0; i < strLen; i++) {
    bits[i] = uint8_t(str[i]);
  }

  return bits;
}

__device__ uint32_t *pad_binary(uint8_t *bits, int size) {

  uint32_t *paddedBits = (uint32_t *)malloc(sizeof(uint32_t) * 16);

  // dividing by 8 to get the number of 8 bit chunks
  int index = size;
  int remainder = index % 4;
  index = index / 4;

  for (int i = 0, j = 0; j < index; i += 4, j++) {
    // multiply each by 2^n to move the binary number n places to the left
    paddedBits[j] = (bits[i] << 24) + (bits[i + 1] << 16) + (bits[i + 2] << 8) +
                    bits[i + 3];
  }

  int i = index * 4;
  uint8_t append = 0x80;

  // Switch statement to determine what goes in the last 32 bit block. This
  // ensures that messages with characters not divisible by four are not
  // shortened.

  // Had to replace the powers with their values as it did not work on the GPU
  switch (remainder) {
  case 1:
    paddedBits[index] = (bits[i] << 24) + (append << 16);
    break;

  case 2:
    paddedBits[index] = (bits[i] << 24) + (bits[i + 1] << 16) + (append << 8);
    break;

  case 3:
    paddedBits[index] =
        (bits[i] << 24) + (bits[i + 1] << 16) + (bits[i + 2] << 8) + append;
    break;

  default:
    paddedBits[index] = append << 24;
    break;
  }

  return paddedBits;
}

// Uses the last 64 bits in order to record the length of the original message.
__device__ void add_length_bits(uint32_t *paddedBits, int sizeBits) {
  uint64_t lengthBits = sizeBits;
  uint64_t divider = 0xFFFFFFFF00000000;

  // Divider to get each half of the 64 bit length by anding them left and
  // right.
  uint32_t leftBits = lengthBits & divider;
  uint32_t rightBits = lengthBits & (divider >> 32);

  paddedBits[14] = leftBits;
  paddedBits[15] = rightBits;
}

/*Computation code*/

__device__ void compute_hash(uint32_t *W, uint32_t *hArr) {

  // declaring variables for computation

  uint32_t a = 0x6a09e667;
  uint32_t b = 0xbb67ae85;
  uint32_t c = 0x3c6ef372;
  uint32_t d = 0xa54ff53a;
  uint32_t e = 0x510e527f;
  uint32_t f = 0x9b05688c;
  uint32_t g = 0x1f83d9ab;
  uint32_t h = 0x5be0cd19;

  uint32_t k[64] = {
      0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
      0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
      0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
      0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
      0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
      0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
      0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
      0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
      0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
      0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
      0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

  // computation beginning

  for (int t = 0; t < 64; t++) {
    uint32_t T1 =
        (h + big_sigma_one(e) + choose(e, f, g) + k[t] + W[t]) % 4294967296;
    uint32_t T2 = (big_sigma_zero(a) + majority(a, b, c)) % 4294967296;
    h = g;
    g = f;
    f = e;
    e = (d + T1) % 4294967296;
    d = c;
    c = b;
    b = a;
    a = (T1 + T2) % 4294967296;
  }

  hArr[0] = a + hArr[0];
  hArr[1] = b + hArr[1];
  hArr[2] = c + hArr[2];
  hArr[3] = d + hArr[3];
  hArr[4] = e + hArr[4];
  hArr[5] = f + hArr[5];
  hArr[6] = g + hArr[6];
  hArr[7] = h + hArr[7];
}

__device__ uint32_t right_rotation(uint32_t bits, int n) {
  // modulo 32 to ensure that ot can't ever shift more places than there are
  // bits
  n = n % 32;

  // optimised here to do the rotate right in one instruction. Improved hashrate
  // by roughly 100,000 hashes per second

  uint32_t shiftedBits = (bits >> n) ^ (bits << (32 - n));
  // uint32_t rotatedBits = bits << (32 - n);
  return shiftedBits;
}

__device__ uint32_t *prepare_message_schedule(uint32_t *paddedBits) {

  uint32_t *schedule = (uint32_t *)malloc(sizeof(uint32_t) * 64);

  for (int i = 0; i < 16; i++) {
    schedule[i] = paddedBits[i];
  }

  for (int t = 16; t <= 63; t++) {
    schedule[t] = sigma_one(schedule[t - 2]) + schedule[t - 7] +
                  sigma_zero(schedule[t - 15]) + (schedule[t - 16]);
  }

  return schedule;
}

// The formula to derive any value for W at position T
/*void build_message_schedule(uint32_t *W) {
  for (int t = 16; t <= 63; t++) {
    W[t] = sigma_one(W[t - 2]) + W[t - 7] + sigma_zero(W[t - 15]) + (W[t - 16]);
  }
}*/

__device__ uint32_t sigma_zero(uint32_t bits) {
  uint32_t sigmaReturn =
      (right_rotation(bits, 7)) ^ (right_rotation(bits, 18)) ^ (bits >> 3);
  return sigmaReturn;
}

__device__ uint32_t sigma_one(uint32_t bits) {
  uint32_t sigmaReturn =
      (right_rotation(bits, 17)) ^ (right_rotation(bits, 19)) ^ (bits >> 10);
  return sigmaReturn;
}

__device__ uint32_t big_sigma_zero(uint32_t bits) {
  uint32_t sigmaReturn = (right_rotation(bits, 2)) ^
                         (right_rotation(bits, 13)) ^
                         (right_rotation(bits, 22));
  return sigmaReturn;
}

__device__ uint32_t big_sigma_one(uint32_t bits) {
  uint32_t sigmaReturn = (right_rotation(bits, 6)) ^
                         (right_rotation(bits, 11)) ^
                         (right_rotation(bits, 25));
  return sigmaReturn;
}

__device__ uint32_t choose(uint32_t x, uint32_t y, uint32_t z) {
  uint32_t chooseReturn = (x & y) ^ (~x & z);
  return chooseReturn;
}

__device__ uint32_t majority(uint32_t x, uint32_t y, uint32_t z) {
  uint32_t majorityReturn = (x & y) ^ (x & z) ^ (y & z);
  return majorityReturn;
}
