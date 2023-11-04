//
// Created by ross on 28/10/23.
//

#ifndef CS408_COMPUTATION_H
#define CS408_COMPUTATION_H
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cmath>

using namespace std;

void compute_hash(bitset<32> W[], u_int32_t hArr[]);

void prepare_message_schedule(bitset<32> schedule[], bitset<32> paddedBits[]);

void build_message_schedule(bitset<32> schedule[]);

ulong sigma_zero(bitset<32> bits);

ulong sigma_one(bitset<32> bits);

ulong big_sigma_zero(bitset<32> bits);

ulong big_sigma_one(bitset<32> bits);

ulong choose(bitset<32> x, bitset<32> y, bitset<32> z);

ulong majority(bitset<32> x, bitset<32> y, bitset<32> z);

class computation {

};


#endif //CS408_COMPUTATION_H
