//
// Created by ross on 28/10/23.
//

#include "computation.h"

struct INITIAL_H_VALUES {
    unsigned int h0 = 0x6a09e667;
    unsigned int h1 = 0xbb67ae85;
    unsigned int h2 = 0x3c6ef372;
    unsigned int h3 = 0xa54ff53a;
    unsigned int h4 = 0x510e527f;
    unsigned int h5 = 0x9b05688c;
    unsigned int h6 = 0x1f83d9ab;
    unsigned int h7 = 0x5be0cd19;
};

struct INITIAL_K_VALUES{
    unsigned int k0 = 0x428a2f98;
    unsigned int k1 = 0x71374491;
    unsigned int k2 = 0xb5c0fbcf;
    unsigned int k3 = 0xe9b5dba5;
    unsigned int k4 = 0x3956c25b;
    unsigned int k5 = 0x59f111f1;
    unsigned int k6 = 0x923f82a4;
    unsigned int k7 = 0xab1c5ed5;
    unsigned int k8 = 0xd807aa98;
    unsigned int k9 = 0x12835b01;
    unsigned int k10 = 0x243185be;
    unsigned int k11 = 0x550c7dc3;
    unsigned int k12 = 0x72be5d74;
    unsigned int k13 = 0x80deb1fe;
    unsigned int k14 = 0x9bdc06a7;
    unsigned int k15 = 0xc19bf174;
    unsigned int k16 = 0xe49b69c1;
    unsigned int k17 = 0xefbe4786;
    unsigned int k18 = 0x0fc19dc6;
    unsigned int k19 = 0x240ca1cc;
    unsigned int k20 = 0x2de92c6f;
    unsigned int k21 = 0x4a7484aa;
    unsigned int k22 = 0x5cb0a9dc;
    unsigned int k23 = 0x76f988da;
    unsigned int k24 = 0x983e5152;
    unsigned int k25 = 0xa831c66d;
    unsigned int k26 = 0xb00327c8;
    unsigned int k27 = 0xbf597fc7;
    unsigned int k28 = 0xc6e00bf3;
    unsigned int k29 = 0xd5a79147;
    unsigned int k30 = 0x06ca6351;
    unsigned int k31 = 0x14292967;
    unsigned int k32 = 0x27b70a85;
    unsigned int k33 = 0x2e1b2138;
    unsigned int k34 = 0x4d2c6dfc;
    unsigned int k35 = 0x53380d13;
    unsigned int k36 = 0x650a7354;
    unsigned int k37 = 0x766a0abb;
    unsigned int k38 = 0x81c2c92e;
    unsigned int k39 = 0x92722c85;
    unsigned int k40 = 0xa2bfe8a1;
    unsigned int k41 = 0xa81a664b;
    unsigned int k42 = 0xc24b8b70;
    unsigned int k43 = 0xc76c51a3;
    unsigned int k44 = 0xd192e819;
    unsigned int k45 = 0xd6990624;
    unsigned int k46 = 0xf40e3585;
    unsigned int k47 = 0x106aa070;
    unsigned int k48 = 0x19a4c116;
    unsigned int k49 = 0x1e376c08;
    unsigned int k50 = 0x2748774c;
    unsigned int k51 = 0x34b0bcb5;
    unsigned int k52 = 0x391c0cb3;
    unsigned int k53 = 0x4ed8aa4a;
    unsigned int k54 = 0x5b9cca4f;
    unsigned int k55 = 0x682e6ff3;
    unsigned int k56 = 0x748f82ee;
    unsigned int k57 = 0x78a5636f;
    unsigned int k58 = 0x84c87814;
    unsigned int k59 = 0x8cc70208;
    unsigned int k60 = 0x90befffa;
    unsigned int k61 = 0xa4506ceb;
    unsigned int k62 = 0xbef9a3f7;
    unsigned int k63 = 0xc67178f2;
};

/*
 * function that takes a 32-bit number and right shifts it by n
 * initially shifts the bits right
 * then shifts left by 32 - n to ensure the ones at the end are rotated to the beginning
 * xor at the end to combine the right and left
*/

bitset<32> right_rotation(bitset<32> bits, int n){
    bitset<32> shiftedBits = bits >> n;
    bitset<32> rotatedBits = bits << 32 - n;
    return shiftedBits ^ rotatedBits;
}