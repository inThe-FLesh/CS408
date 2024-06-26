//
// Created by ross on 28/10/23.
//

#ifndef CS408_PREPROCESSING_H
#define CS408_PREPROCESSING_H
#include <bitset>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>

using std::bitset;
using std::string;

uint8_t *string_to_binary(const string &str);

uint32_t *pad_binary(uint8_t *bits, int size);

void add_length_bits(uint32_t *paddedBits, int sizeBits);

class preprocessing {};

#endif // CS408_PREPROCESSING_H
