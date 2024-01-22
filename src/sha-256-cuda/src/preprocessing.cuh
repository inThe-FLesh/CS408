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

__host__ uint8_t *string_to_binary(const string &str);

__device__ uint32_t *pad_binary(uint8_t *bits, int size);

__device__ void add_length_bits(uint32_t *paddedBits, int sizeBits);

class preprocessing {};

#endif // CS408_PREPROCESSING_H
