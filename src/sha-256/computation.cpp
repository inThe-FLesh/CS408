//
// Created by ross on 28/10/23.
//
#include "computation.h"
#include <cstdint>
#include <stdexcept>
/*
 * function that takes a 32-bit number and right shifts it by n
 * initially shifts the bits right
 * then shifts left by 32 - n to ensure the ones at the end are rotated to the
 * beginning xor at the end to combine the right and left
 */

void compute_hash(uint32_t *W, uint32_t *hArr) {

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

uint32_t *prepare_message_schedule(uint32_t *paddedBits) {

  uint32_t *schedule = (uint32_t *)malloc(sizeof(uint32_t) * 64);

  if (schedule == NULL) {
    throw std::runtime_error(
        "prepare_message_schedule failed to allocate memory for schedule");
  }

  for (int i = 0; i < 16; i++) {
    schedule[i] = paddedBits[i];
  }

  for (int t = 16; t <= 63; t++) {
    schedule[t] = sigma_one(schedule[t - 2]) + schedule[t - 7] +
                  sigma_zero(schedule[t - 15]) + (schedule[t - 16]);
  }

  return schedule;
}

uint32_t right_rotation(uint32_t bits, int n) {
  // modulo 32 to ensure that ot can't ever shift more places than there are
  // bits
  n = n % 32;

  // optimised here to do the rotate right in one instruction. Improved hashrate
  // by roughly 100,000 hashes per second

  uint32_t shiftedBits = (bits >> n) ^ (bits << (32 - n));
  // uint32_t rotatedBits = bits << (32 - n);
  return shiftedBits;
}

uint32_t sigma_zero(uint32_t bits) {
  uint32_t sigmaReturn =
      (right_rotation(bits, 7)) ^ (right_rotation(bits, 18)) ^ (bits >> 3);
  return sigmaReturn;
}

uint32_t sigma_one(uint32_t bits) {
  uint32_t sigmaReturn =
      (right_rotation(bits, 17)) ^ (right_rotation(bits, 19)) ^ (bits >> 10);
  return sigmaReturn;
}

uint32_t big_sigma_zero(uint32_t bits) {
  uint32_t sigmaReturn = (right_rotation(bits, 2)) ^
                         (right_rotation(bits, 13)) ^
                         (right_rotation(bits, 22));
  return sigmaReturn;
}

uint32_t big_sigma_one(uint32_t bits) {
  uint32_t sigmaReturn = (right_rotation(bits, 6)) ^
                         (right_rotation(bits, 11)) ^
                         (right_rotation(bits, 25));
  return sigmaReturn;
}

uint32_t choose(uint32_t x, uint32_t y, uint32_t z) {
  uint32_t chooseReturn = (x & y) ^ (~x & z);
  return chooseReturn;
}

uint32_t majority(uint32_t x, uint32_t y, uint32_t z) {
  uint32_t majorityReturn = (x & y) ^ (x & z) ^ (y & z);
  return majorityReturn;
}
