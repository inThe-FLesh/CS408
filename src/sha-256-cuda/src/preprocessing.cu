//
// Created by ross on 28/10/23.
//

#include "preprocessing.cuh"
#include <cstdint>

// Convert the string into binary representation. 8 bits per character.
uint8_t *string_to_binary(const string &str) {
  // breaks up each word in the string to an 8-bit binary number and adds them
  // to  the array.
  uint8_t *bits = (uint8_t *)malloc(sizeof(uint8_t) * str.size());

  for (int i = 0; i < str.length(); i++) {
    bits[i] = uint8_t(str[i]);
  }

  return bits;
}

// divides the characters into 32 bit blocks then appends a single one and pads
// with zeros.
uint32_t *pad_binary(uint8_t *bits, int size) {

  uint32_t *paddedBits = (uint32_t *)malloc(sizeof(uint32_t) * 16);

  // dividing by 8 to get the number of 8 bit chunks
  int index = size;
  int remainder = index % 4;
  index = index / 4;

  for (int i = 0, j = 0; j < index; i += 4, j++) {
    // multiply each by 2^n to move the binary number n places to the left
    paddedBits[j] = bits[i] * pow(2, 24) + bits[i + 1] * pow(2, 16) +
                    bits[i + 2] * pow(2, 8) + bits[i + 3];
  }

  int i = index * 4;
  uint8_t append = 0x80;

  // Switch statement to determine what goes in the last 32 bit block. This
  // ensures that messages with characters not divisible by four are not
  // shortened.
  switch (remainder) {
  case 1:
    paddedBits[index] = bits[i] * pow(2, 24) + append * pow(2, 16);
    break;

  case 2:
    paddedBits[index] =
        bits[i] * pow(2, 24) + bits[i + 1] * pow(2, 16) + append * pow(2, 8);
    break;

  case 3:
    paddedBits[index] = bits[i] * pow(2, 24) + bits[i + 1] * pow(2, 16) +
                        bits[i + 2] * pow(2, 8) + append;
    break;

  default:
    paddedBits[index] = append * pow(2, 24);
    break;
  }

  return paddedBits;
}

// Uses the last 64 bits in order to record the length of the original message.
void add_length_bits(uint32_t *paddedBits, int sizeBits) {
  uint64_t lengthBits = sizeBits;
  uint64_t divider = 0xFFFFFFFF00000000;

  // Divider to get each half of the 64 bit length by anding them left and
  // right.
  uint32_t leftBits = lengthBits & divider;
  uint32_t rightBits = lengthBits & (divider >> 32);

  paddedBits[14] = leftBits;
  paddedBits[15] = rightBits;
}
