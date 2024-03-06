#include "converter.h"
#include <cassert>
#include <cinttypes>
#include <cmath>
#include <cstdint>
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
  }

  uint8_t *Encrypt() {
    Converter converter;
    int byteRemainder = numBytes % 4;

    numBytes = numBytes / 4;
    uint8_t *nextText = cText;
    uint32_t *cText32Bit = (uint32_t *)malloc(sizeof(uint32_t) * numBytes + 1);

    for (int i = 0; i < numBytes; i++) {
      cText32Bit[i] = converter.bytes_to_32bit(nextText, 4);
      nextText = &nextText[4];
    }

    cText32Bit[numBytes + 1] = converter.bytes_to_32bit(cText, byteRemainder);

    numBytes += byteRemainder;

// Work this out
    for (int n = 0; n < numBytes; n++) {
        uint32_t *cipherRound = (uint32_t *)malloc(sizeof(uint32_t) * 2);

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
    }

    cText32Bit[1] = cText32Bit[1] ^ P[17];
    cText32Bit[0] = cText32Bit[0] ^ P[16];

    return converter.bits_to_bytes(append32bits(cText32Bit), 64);
  }

private:
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

  static uint8_t *getQuarters(uint32_t block) {
    uint8_t *quarters = (uint8_t *)malloc(sizeof(uint8_t) * 4);
    uint8_t divider = 0xff;

    // starting i at one so I can use it to control the right shift amount
    for (int i = 1; i <= 4; i++) {
      quarters[i] = divider & (block >> (32 - (8 * i)));
    }

    return quarters;
  }

  static uint64_t append32bits(uint32_t *bits){
      uint64_t output = bits[0];
      output = output << 32;
      output += bits[1];

      return output;
  }
};
