//
// Created by ross on 28/10/23.
//

#ifndef CS408_COMPUTATION_H
#define CS408_COMPUTATION_H
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cmath>

using std::bitset;
using std::cout;
using std::endl;

void compute_hash(const u_int32_t W[], u_int32_t* hArr);

__device__ __host__ u_int32_t right_rotation(u_int32_t bits, int n);

__global__ void prepare_message_schedule(u_int32_t* schedule, const u_int32_t* paddedBits);

void build_message_schedule(u_int32_t* W);

__device__ __host__ u_int32_t sigma_zero(u_int32_t bits);

__device__ __host__ u_int32_t sigma_one(u_int32_t bits);

u_int32_t big_sigma_zero(u_int32_t bits);

u_int32_t big_sigma_one(u_int32_t bits);

u_int32_t choose(bitset<32> x, bitset<32> y, bitset<32> z);

u_int32_t majority(bitset<32> x, bitset<32> y, bitset<32> z);

class computation {

};


#endif //CS408_COMPUTATION_H
