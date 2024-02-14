#include <cinttypes>
#include <cstdint>
#include <cstdlib>

class Blowfish {
private:
  uint32_t *P;
  uint32_t **S;
  uint64_t buffer;

public:
  Blowfish(uint32_t *P, uint32_t **S, uint64_t buffer) {
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
