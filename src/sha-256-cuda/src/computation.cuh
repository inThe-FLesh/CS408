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

using std::bitset;
using std::cout;
using std::endl;

__device__ void compute_hash(uint32_t *W, uint32_t *hArr);

__device__ uint32_t right_rotation(uint32_t bits, int n);

__device__ uint32_t *prepare_message_schedule(uint32_t *paddedBits);

__device__ void build_message_schedule(uint32_t *W);

__device__ uint32_t sigma_zero(uint32_t bits);

__device__ uint32_t sigma_one(uint32_t bits);

__device__ uint32_t big_sigma_zero(uint32_t bits);

__device__ uint32_t big_sigma_one(uint32_t bits);

__device__ uint32_t choose(uint32_t x, uint32_t y, uint32_t z);

__device__ uint32_t majority(uint32_t x, uint32_t y, uint32_t z);

class computation {};

#endif // CS408_COMPUTATION_H
