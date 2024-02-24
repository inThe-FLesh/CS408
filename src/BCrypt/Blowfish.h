#include <cassert>
#include <cinttypes>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

// abstract class that is used to convert uints to strings and vice versa
// in a way that suits the algorithm

struct Converter {
  virtual uint32_t stringToUint32(std::string str) {
    uint32_t output = 0;
    assert(str.length() <= 4);
    for (int i = 0; i < str.length(); i++) {
      uint8_t character = (uint8_t)str[i];
      output += character << (24 - (8 * i));
    }

    return output;
  }

  virtual uint64_t stringToUint64(std::string str) {
    uint64_t output = 0;
    assert(str.length() <= 8);
    for (int i = 0; i < str.length(); i++) {
      uint8_t character = (uint8_t)str[i];
      output += character << (56 - (8 * i));
    }

    return output;
  }

  virtual std::string uint64_tToString(uint64_t cipher) {
    const uint8_t divider = 0xff;
    std::string output = "";
    for (int i = 0; i < 8; i++) {
      output += (char)(cipher & divider);
      cipher = cipher >> 8;
    }
    return output;
  }
};

// end of abstract class

// 2 classes that are used for blowfish encryption
// one for the EksBlowfish part of the algorithm
// and the other for when we encrypt OrpheanBeholderScryDoubt
class EksBlowfish {
private:
  uint32_t *P;
  uint32_t **S;
  uint64_t buffer;

public:
  EksBlowfish(uint32_t *P, uint32_t **S, uint64_t buffer) {
    this->P = P;
    this->S = S;
    this->buffer = buffer;
  }

  uint64_t Encrypt() {
    uint32_t *bufferHalves = splitBuffer();
    uint32_t leftBuffer;
    uint32_t rightBuffer;
    uint64_t output;

    for (int i = 0; i < 16; i++) {
      rightBuffer = bufferHalves[0];
      leftBuffer = bufferHalves[0] ^ P[i];
      leftBuffer = f(bufferHalves[0]) ^ bufferHalves[1];

      bufferHalves[0] = leftBuffer;
      bufferHalves[1] = rightBuffer;
    }

    rightBuffer = bufferHalves[1] ^ P[16];
    leftBuffer = bufferHalves[0] ^ P[17];

    free(bufferHalves);

    output = leftBuffer;
    output = (output << 32) + rightBuffer;

    return output;
  }

private:
  uint32_t *splitBuffer() {
    uint32_t *bufferHalves = (uint32_t *)malloc(sizeof(uint32_t) * 2);
    uint32_t divider = 0xffffffff;

    bufferHalves[0] = (buffer >> 32) & divider;
    bufferHalves[1] = buffer & divider;

    return bufferHalves;
  }

  uint32_t f(uint32_t word) {
    uint8_t divider = 0xff;
    uint8_t *quarters = (uint8_t *)malloc(sizeof(uint8_t) * 4);
    uint32_t output;

    for (int i = 0; i < 4; i++) {
      quarters[i] = (word >> 8 * i) ^ divider;
    }

    // this takes the first 2 bits and uses them as the index for the column and
    // then it takes the last 6 bits and uses them to get the row
    output = (S[quarters[0] >> 6][quarters[0] & 0x3f] +
              S[quarters[1] >> 6][quarters[1] & 0x3f]) %
             4294967296;

    output = output ^ S[quarters[2] >> 6][quarters[2] & 0x3f];

    output = output + S[quarters[3] >> 6][quarters[3] & 0x3f];

    return output;
  }
};

class Blowfish {
private:
  int numChunks;
  uint32_t *P;
  uint32_t **S;
  std::string cText;

public:
  Blowfish(uint32_t *P, uint32_t **S, std::string cText) {
    this->P = P;
    this->S = S;
    this->cText = cText;
  }

  uint64_t *EncryptECB() {
    uint64_t *chunks = getChunks(cText);

    for (int n = 0; n < numChunks; n++) {
      uint32_t *halves = getHalves(chunks[n]);
      uint32_t left = halves[0];
      uint32_t right = halves[1];

      for (int i = 0; i < 16; i++) {
        left = left ^ P[i];
        right = f(left) ^ right;

        uint32_t tempLeft = left;

        left = right;
        right = tempLeft;
      }

      // the final swap of left and right happens here
      // without wasting instructions swapping the variables
      left = left ^ P[16];
      right = right ^ P[17];

      halves[0] = right;
      halves[1] = left;

      uint64_t output = append64(halves);
      chunks[n] = output;
    }

    return chunks;
  }

private:
  uint32_t f(uint32_t block) {
    uint8_t *quarters = getQuarters(block);
    uint32_t s1 = S[0][quarters[0]];
    uint32_t s2 = S[1][quarters[1]];
    uint32_t s3 = S[2][quarters[2]];
    uint32_t s4 = S[3][quarters[3]];

    // addition mod 2^32
    s2 = (s1 + s2) % 4294967296;
    s3 = s3 ^ s2;
    s4 = (s3 + s4) % 4294967296;

    return s4;
  }

  uint64_t append64(uint32_t *halves) {
    uint64_t left = halves[0];
    uint64_t right = halves[1];

    uint64_t output = (left << 32) + right;

    return output;
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

  uint32_t *getHalves(uint64_t chunk) {
    uint64_t divider = 0x00000000ffffffff;
    uint32_t left = (chunk >> 32) & divider;
    uint32_t right = chunk & divider;

    uint32_t *halves = (uint32_t *)malloc(sizeof(uint32_t) * 2);

    halves[0] = left;
    halves[1] = right;

    return halves;
  }

  uint64_t *getChunks(std::string cText) {
    // getting the length of string in bits
    // then finding the number of 64 bit chinks
    int length = cText.length();
    assert(length != 0);

    // 8 is used here as 64 bits is equivalent to 8 bytes
    numChunks = length / 8;

    // using the PKCS#5 standard here and appending
    // the the hex value of the number of padding characters needed
    if (numChunks == 0) {
      size_t padLength = length % 8;
      for (int i = 0; i < padLength; i++) {
        char appendedChar = (char)padLength;
        cText.append(padLength, appendedChar);
      }
      numChunks = 1;
    }

    uint64_t *chunks = (uint64_t *)malloc(sizeof(uint32_t) * numChunks);

    int start = 0;
    int end = 8;

    for (int i = 0; i < numChunks; i++) {
      Converter converter;
      chunks[i] = converter.stringToUint64(cText.substr(start, end));
      start += 8;
    }

    return chunks;
  }
};
