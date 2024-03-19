#include "converter.cuh"
#include <cassert>
#include <cinttypes>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <sys/types.h>
// 2 classes that are used for blowfish encryption
// one for the EksBlowfish part of the algorithm
// and the other for when we encrypt OrpheanBeholderScryDoubt
//
// These classes should use an interface

__device__ uint8_t *getQuarters(uint32_t block) {
  uint8_t *quarters = (uint8_t *)malloc(sizeof(uint8_t) * 4);
  uint8_t divider = 0xff;

  // starting i at one, so I can use it to control the right shift amount
  for (int i = 1; i <= 4; i++) {
    quarters[i - 1] = divider & (block >> (32 - (8 * i)));
  }

  return quarters;
}

__device__ uint32_t f(uint32_t block, uint32_t *S0, uint32_t *S1, uint32_t *S2,
                      uint32_t *S3) {
  uint8_t *quarters = getQuarters(block);
  uint32_t s0Val = S0[quarters[0]];
  uint32_t s1Val = S1[quarters[1]];
  uint32_t s2Val = S2[quarters[2]];
  uint32_t s3Val = S3[quarters[3]];

  size_t subSize = (sizeof(uint32_t) * 4);

  free(quarters);

  // addition mod 2^32
  s1Val = (s0Val + s1Val) % 4294967296;
  s2Val = s2Val ^ s1Val;
  s3Val = (s2Val + s3Val) % 4294967296;

  return s3Val;
}

__device__ uint64_t append32bits(uint32_t *bits) {
  uint64_t output = bits[0];
  output = output << 32;
  output += bits[1];

  return output;
}

__global__ void kernel(uint32_t *P, uint32_t *S0, uint32_t *S1, uint32_t *S2,
                       uint32_t *S3, uint32_t *cText32Bit, int chunks,
                       uint64_t *cipherOut) {

  uint32_t *cipherRound = (uint32_t *)malloc(sizeof(uint32_t) * 3);

  int tid = threadIdx.x;

  if (tid <= chunks && tid % 2 == 0) {
    cipherRound[0] = cText32Bit[tid];
    cipherRound[1] = cText32Bit[tid++];

    for (int i = 0; i < 16; i++) {
      // doing the switch of the left and right halves with the mod of i
      // pointers are used so that I don't have to waste instructions by
      // putting the values back into the array
      uint32_t *leftBytes = &cipherRound[0];
      uint32_t *rightBytes = &cipherRound[1];

      *leftBytes = *leftBytes ^ P[i];
      *leftBytes = f(*leftBytes, S0, S1, S2, S3);

      *rightBytes = *rightBytes ^ *leftBytes;

      cipherRound[2] = cipherRound[0];
      cipherRound[0] = cipherRound[1];
      cipherRound[1] = cipherRound[2];
    }

    cipherRound[1] = cipherRound[1] ^ P[17];
    cipherRound[0] = cipherRound[0] ^ P[16];

    cipherOut[tid / 2] = append32bits(cipherRound);
  }
}

class Blowfish {
private:
  int numBytes;
  uint32_t *P;
  uint32_t **S;
  uint8_t *cText;

public:
  Blowfish(uint32_t *P, uint32_t **S, uint8_t *cText, int numBytes) {
    this->P = P;
    this->S = S;
    this->cText = cText;
    this->numBytes = numBytes;

    size_t pBoxSize = sizeof(uint32_t) * 18;
    size_t sBoxSize = sizeof(uint32_t) * 256;
  }

  ~Blowfish() {}

  uint8_t **Encrypt() {
    int chunks = numBytes / 4;

    if (chunks > 1) {
      return cudaEncrypt();
    }

    return cpuEncrypt();
  }

private:
  uint32_t f(uint32_t block) {
    uint8_t *quarters = getQuarters(block);
    uint32_t s1 = S[0][quarters[0]];
    uint32_t s2 = S[1][quarters[1]];
    uint32_t s3 = S[2][quarters[2]];
    uint32_t s4 = S[3][quarters[3]];

    size_t subSize = (sizeof(uint32_t) * 4);

    free(quarters);

    // addition mod 2^32
    s2 = (s1 + s2) % 4294967296;
    s3 = s3 ^ s2;
    s4 = (s3 + s4) % 4294967296;

    return s4;
  }

  static uint8_t *getQuarters(uint32_t block) {
    uint8_t *quarters = (uint8_t *)malloc(sizeof(uint8_t) * 4);
    uint8_t divider = 0xff;

    // starting i at one, so I can use it to control the right shift amount
    for (int i = 1; i <= 4; i++) {
      quarters[i - 1] = divider & (block >> (32 - (8 * i)));
    }

    return quarters;
  }

  static uint64_t append32bits(uint32_t *bits) {
    uint64_t output = bits[0];
    output = output << 32;
    output += bits[1];

    return output;
  }

  uint8_t **cpuEncrypt() {
    Converter converter;
    int byteRemainder = numBytes % 4;

    numBytes = numBytes / 4;
    uint8_t *nextText = cText;
    uint32_t *cText32Bit = (uint32_t *)malloc(sizeof(uint32_t) * numBytes + 1);

    for (int i = 0; i < numBytes; i++) {
      cText32Bit[i] = converter.bytes_to_32bit(nextText, 4);
      nextText = &nextText[4];
    }

    // this is used to pad the message if there aren't enough 32 bit pairs
    if (numBytes % 2 != 0) {
      cText32Bit[numBytes] = converter.bytes_to_32bit(nextText, byteRemainder);
      cText32Bit[numBytes + 1] = 0;
      numBytes += 1;
    }

    uint8_t **blocks = (uint8_t **)malloc(sizeof(uint8_t *) * numBytes);

    // Work this out
    assert(numBytes % 2 == 0);
    for (int n = 0, j = 0; n < numBytes; n += 2, j++) {
      uint8_t *block;
      uint32_t *cipherRound = (uint32_t *)malloc(sizeof(uint32_t) * 3);
      cipherRound[0] = cText32Bit[n];
      cipherRound[1] = cText32Bit[n + 1];

      for (int i = 0; i < 16; i++) {
        // doing the switch of the left and right halves with the mod of i
        // pointers are used so that I don't have to waste instructions by
        // putting the values back into the array
        uint32_t *leftBytes = &cipherRound[0];
        uint32_t *rightBytes = &cipherRound[1];

        *leftBytes = *leftBytes ^ P[i];
        *leftBytes = f(*leftBytes);

        *rightBytes = *rightBytes ^ *leftBytes;

        cipherRound[2] = cipherRound[0];
        cipherRound[0] = cipherRound[1];
        cipherRound[1] = cipherRound[2];
      }

      cipherRound[1] = cipherRound[1] ^ P[17];
      cipherRound[0] = cipherRound[0] ^ P[16];

      uint64_t cipherOut = append32bits(cipherRound);

      block = converter.bits_to_bytes(cipherOut, 64);

      blocks[j] = block;
    }

    return blocks;
  }

  uint8_t **cudaEncrypt() {
    Converter converter;
    int byteRemainder = numBytes % 4;

    int chunks = numBytes / 4;
    uint8_t *nextText = cText;
    size_t ctextSize = sizeof(uint32_t) * chunks + 1;
    uint32_t *cText32Bit = (uint32_t *)malloc(ctextSize);
    uint32_t *dcText32Bit;

    // declaring the ctext array on device
    cudaMalloc(&dcText32Bit, ctextSize);

    for (int i = 0; i < chunks; i++) {
      cText32Bit[i] = converter.bytes_to_32bit(nextText, 4);
      nextText = &nextText[4];
    }

    // this is used to pad the message if there aren't enough 32 bit pairs
    if (chunks % 2 != 0) {
      cText32Bit[chunks] = converter.bytes_to_32bit(nextText, byteRemainder);
      cText32Bit[chunks + 1] = 0;
      chunks += 1;
    }

    uint8_t **blocks = (uint8_t **)malloc(sizeof(uint8_t *) * chunks);

    // copying p and Sboxes to device for kernel function
    uint32_t *dP;
    uint32_t *dS0;
    uint32_t *dS1;
    uint32_t *dS2;
    uint32_t *dS3;
    uint64_t *dCipherOut;

    size_t pBoxSize = sizeof(uint32_t) * 18;
    size_t sBoxSize = sizeof(uint32_t) * 256;
    size_t cipherOutSize = sizeof(uint64_t) * chunks / 2;

    cudaMalloc(&dP, pBoxSize);
    cudaMalloc(&dS0, sBoxSize);
    cudaMalloc(&dS1, sBoxSize);
    cudaMalloc(&dS2, sBoxSize);
    cudaMalloc(&dS3, sBoxSize);
    cudaMalloc(&dCipherOut, cipherOutSize);

    cudaMemcpy(dP, P, pBoxSize, cudaMemcpyHostToDevice);
    cudaMemcpy(dS0, S[0], sBoxSize, cudaMemcpyHostToDevice);
    cudaMemcpy(dS1, S[1], sBoxSize, cudaMemcpyHostToDevice);
    cudaMemcpy(dS2, S[2], sBoxSize, cudaMemcpyHostToDevice);
    cudaMemcpy(dS3, S[3], sBoxSize, cudaMemcpyHostToDevice);
    cudaMemcpy(dcText32Bit, cText32Bit, ctextSize, cudaMemcpyHostToDevice);

    kernel<<<1, chunks>>>(dP, dS0, dS1, dS2, dS3, dcText32Bit, chunks,
                          dCipherOut);

    uint64_t *cipherOut = (uint64_t *)malloc(cipherOutSize);

    cudaDeviceSynchronize();

    cudaMemcpy(cipherOut, dCipherOut, cipherOutSize, cudaMemcpyDeviceToHost);

    cudaError_t error = cudaGetLastError();

    if (error != cudaSuccess) {
      std::cerr << "Cuda Error: " << error << std::endl;
    }

    for (int i = 0; i < chunks / 2; i++) {
      blocks[i] = converter.bits_to_bytes(cipherOut[i], 64);
    }

    return blocks;
  }
};
