//
// Created by ross on 28/10/23.
//

#ifndef CS408_COMPUTATION_H
#define CS408_COMPUTATION_H
#include <bitset>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sys/types.h>

using std::bitset;
using std::cout;
using std::endl;

__global__ void cuda_compute(uint32_t W[][64], uint32_t hArr[][64]);

bitset<32> right_rotation(bitset<32> bits, int n);

void prepare_message_schedule(bitset<32> schedule[], bitset<32> paddedBits[]);

void build_message_schedule(bitset<32> schedule[]);

ulong sigma_zero(bitset<32> bits);

ulong sigma_one(bitset<32> bits);

__device__ ulong big_sigma_zero(ulong bits);

__device__ ulong big_sigma_one(ulong bits);

__device__ ulong choose(bitset<32> x, bitset<32> y, bitset<32> z);

__device__ ulong majority(bitset<32> x, bitset<32> y, bitset<32> z);

__device__ bitset<32> device_right_rotation(bitset<32> bits, int n);

class computation {};

#endif // CS408_COMPUTATION_H
