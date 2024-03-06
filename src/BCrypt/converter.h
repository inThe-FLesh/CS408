#include <cstdint>
#include <cstdlib>
#include <string>

struct Converter {
  virtual uint64_t bytes_to_64bit(uint8_t *bytes, int numBytes) {
    uint64_t output = 0;
    for (int i = 0; i < numBytes; i++) {
      output += bytes[i];
      output = output << 8;
    }

    output += bytes[numBytes - 1];

    return output;
  }
  virtual uint32_t bytes_to_32bit(uint8_t *bytes, int numBytes) {
    uint32_t output = 0;
    for (int i = 0; i < numBytes - 1; i++) {
      output += bytes[i];
      output = output << 8;
    }

    output += bytes[numBytes - 1];

    return output;
  }

  // this function takes the number of bytes to be converted such as 64 or 32 as
  // an int value and returns an array of those bits as bytes
  virtual uint8_t *bits_to_bytes(uint64_t bits, int numberOfBits) {
    uint8_t divider = 0xff;
    uint8_t *bytes = (uint8_t *)malloc(sizeof(uint8_t) * numberOfBits / 8);

    for (int i = 0; i < numberOfBits / 8; i++) {
      bytes[i] = divider & bits;
      bits = bits >> 8;
    }

    return bytes;
  }

  virtual uint32_t *split_64bit(uint64_t bits) {
    uint32_t divider = 0xffffffff;
    uint32_t *halves = (uint32_t *)malloc(sizeof(uint32_t) * 2);

    halves[0] = (bits >> 32) & divider;
    halves[1] = bits & divider;

    return halves;
  }
};
