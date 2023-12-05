//
// Created by ross on 28/10/23.
//

#include "headers/preprocessing.h"

// Convert the string into binary representation. 8 bits per character.
void string_to_binary(const string &str, bitset<8> bits[]) {
    // breaks up each word in the string to an 8-bit binary number and adds them
    // to  the array.
    for (int i = 0; i < str.length(); i++) {
        bits[i] = bitset<8>(str[i]);
    }
}

// divides the characters into 32 bit blocks then appends a single one and pads
// with zeros.
void pad_binary(u_int32_t* paddedBits, bitset<8> bits[], unsigned long size) {

    // dividing by 8 to get the number of 8 bit chunks
    int index = (int)size / 8;
    int remainder = index % 4;
    index = index / 4;

    for (int i = 0, j = 0; j < index; i += 4, j++) {
        // multiply each by 2^n to move the binary number n places to the left
        paddedBits[j] = bits[i].to_ullong() * pow(2, 24) +
                                   bits[i + 1].to_ullong() * pow(2, 16) +
                                   bits[i + 2].to_ullong() * pow(2, 8) +
                                   bits[i + 3].to_ullong();
    }

    int i = index * 4;
    bitset<8> append = 0x80;

    // Switch statement to determine what goes in the last 32 bit block. This
    // ensures that messages with characters not divisible by four are not
    // shortened.
    switch (remainder) {
        case 1:
            paddedBits[index] = bits[i].to_ullong() * pow(2, 24) +
                                           append.to_ullong() * pow(2, 16);
            break;

        case 2:
            paddedBits[index] = bits[i].to_ullong() * pow(2, 24) +
                                           bits[i + 1].to_ullong() * pow(2, 16) +
                                           append.to_ullong() * pow(2, 8);
            break;

        case 3:
            paddedBits[index] =
                    bits[i].to_ullong() * pow(2, 24) +
                               bits[i + 1].to_ullong() * pow(2, 16) +
                               bits[i + 2].to_ullong() * pow(2, 8) + append.to_ullong();
            break;

        default:
            paddedBits[index] = append.to_ullong() * pow(2, 24);
            break;
    }
}

// Uses the last 64 bits in order to record the length of the original message.
void add_length_bits(u_int32_t* paddedBits, unsigned long sizeBits) {
    u_int64_t lengthBits = sizeBits;
    u_int64_t divider = 0xFFFFFFFF00000000;

    // Divider to get each half of the 64 bit length by anding them left and
    // right.
    u_int32_t leftBits = lengthBits & divider;
    u_int32_t rightBits = lengthBits & (divider >> 32);

    paddedBits[14] = leftBits;
    paddedBits[15] = rightBits;
}
