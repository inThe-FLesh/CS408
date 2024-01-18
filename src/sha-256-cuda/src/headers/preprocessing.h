//
// Created by ross on 28/10/23.
//

#ifndef CS408_PREPROCESSING_H
#define CS408_PREPROCESSING_H
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cmath>

using std::string;
using std::bitset;

void string_to_binary(const string& str, bitset<8> bits[]);

void pad_binary(u_int32_t* paddedBits, bitset<8> bits[], unsigned long size) ;

void add_length_bits(u_int32_t* paddedBits, unsigned long sizeBits);




class preprocessing {

};


#endif //CS408_PREPROCESSING_H
