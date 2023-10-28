//
// Created by ross on 28/10/23.
//

#ifndef CS408_PREPROCESSING_H
#define CS408_PREPROCESSING_H
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cmath>

using namespace std;

void string_to_binary(const string& str, bitset<8> bits[]);

void pad_binary(bitset<32> paddedBits[], bitset<8> bits[], int size);

void add_length(bitset<32> paddedBits[], int sizeBits);



class preprocessing {

};


#endif //CS408_PREPROCESSING_H
