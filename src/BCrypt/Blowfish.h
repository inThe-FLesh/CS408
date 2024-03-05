#include <cassert>
#include <cinttypes>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

// 2 classes that are used for blowfish encryption
// one for the EksBlowfish part of the algorithm
// and the other for when we encrypt OrpheanBeholderScryDoubt
//
// These classes should use an interface

class Blowfish {
private:
  int numChunks;
  uint32_t *P;
  uint32_t **S;
  uint8_t *cText;

public:
  Blowfish(uint32_t *P, uint32_t **S, uint8_t *cText) {
    this->P = P;
    this->S = S;
    this->cText = cText;
  }

  uint8_t *Encrypt() {
    uint32_t *cText32Bit = convert_to_32bit(cText);

    for (int i = 0; i < 16; i++) {
      // doing the switch of the left and right halves with the mod of i
      // pointers are used so that I don't have to waste instructions by putting
      // the values back into the array
      uint32_t *leftBytes = &cText32Bit[i % 2];
      uint32_t *rightBytes = &cText32Bit[(i + 1) % 2];

      *leftBytes = *leftBytes ^ P[i];
      *leftBytes = f(*leftBytes);

      *rightBytes = *rightBytes ^ *leftBytes;
    }

    cText32Bit[1] = cText32Bit[1] ^ P[17];
    cText32Bit[0] = cText32Bit[0] ^ P[16];

    return convert_to_bytes(cText32Bit);
  }

private:
  uint8_t *convert_to_bytes(uint32_t *bits) {
    uint8_t divider = 0xff;
    uint8_t *bytes = (uint8_t *)malloc(sizeof(uint8_t) * 8);
    uint32_t leftBits = bits[0];
    uint32_t rightBits = bits[1];

    for (int i = 0; i < 4; i++) {
      uint8_t test = divider & leftBits;
      bytes[i] = divider & leftBits;
      leftBits = leftBits >> 8;
    }

    for (int i = 4; i < 8; i++) {
      uint8_t test2 = divider & rightBits;
      bytes[i] = divider & rightBits;
      rightBits = rightBits >> 8;
    }

    return bytes;
  }

  uint32_t *convert_to_32bit(uint8_t *bytes) {
    uint32_t leftBytes = 0;
    uint32_t rightBytes = 0;
    uint32_t *output = (uint32_t *)malloc(sizeof(uint32_t) * 2);

    for (int i = 0; i < 3; i++) {
      leftBytes += bytes[i];
      leftBytes = leftBytes << 8;
    }

    leftBytes += bytes[3];

    for (int i = 4; i < 7; i++) {
      rightBytes += bytes[i];
      rightBytes = rightBytes << 8;
    }

    rightBytes += bytes[7];

    output[0] = leftBytes;
    output[1] = rightBytes;

    return output;
  }

  uint32_t f(uint32_t block) {
    uint8_t *quarters = getQuarters(block);
    uint32_t s1 = S[0][quarters[0]];
    uint32_t s2 = S[1][quarters[1]];
    uint32_t s3 = S[2][quarters[2]];
    uint32_t s4 = S[3][quarters[3]];

    free(quarters);

    // addition mod 2^32
    s2 = (s1 + s2) % 4294967296;
    s3 = s3 ^ s2;
    s4 = (s3 + s4) % 4294967296;

    return s4;
  }

  uint8_t *getQuarters(uint32_t block) {
    uint8_t *quarters = (uint8_t *)malloc(sizeof(uint8_t) * 4);
    uint8_t divider = 0xff;

    // starting i at one so I can use it to control the right shift amount
    for (int i = 1; i <= 4; i++) {
      quarters[i] = divider & (block >> (32 - (8 * i)));
    }

    return quarters;
  }
};
