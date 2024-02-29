//
// Created by ross on 27/10/23.
//

#ifndef CS408_SHA256_H
#define CS408_SHA256_H
#include <bitset>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cuda_runtime.h>
#include <iomanip>
#include <iostream>
#include <strings.h>
#include <sys/time.h>
#include <sys/types.h>

using std::bitset;
using std::cout;
using std::endl;
using std::string;
using namespace std::chrono;
using namespace std::chrono_literals;
using std::cin;
using std::cout;
using std::dec;
using std::hex;
using std::setfill;
using std::setw;
using std::string;

void sha();

uint8_t *string_to_binary(const char *str, const int strLen);

uint32_t *pad_binary(uint8_t *bits, int size);

void add_length_bits(uint32_t *paddedBits, int sizeBits);

void compute_hash(uint32_t *W, uint32_t *hArr);

uint32_t right_rotation(uint32_t bits, int n);

__device__ uint32_t device_right_rotation(uint32_t bits, int n);

__global__ void prepare_message_schedule(uint32_t *paddedBits,
                                         uint32_t *schedule);

void build_message_schedule(uint32_t *W);

__device__ uint32_t sigma_zero(uint32_t bits);

__device__ uint32_t sigma_one(uint32_t bits);

uint32_t big_sigma_zero(uint32_t bits);

uint32_t big_sigma_one(uint32_t bits);

uint32_t choose(uint32_t x, uint32_t y, uint32_t z);

uint32_t majority(uint32_t x, uint32_t y, uint32_t z);

class SHA256 {};

#endif // CS408_SHA256_H
