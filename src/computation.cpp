//
// Created by ross on 28/10/23.
//

#include "computation.h"

u_int32_t a = 0x6a09e667;
u_int32_t b = 0xbb67ae85;
u_int32_t c = 0x3c6ef372;
u_int32_t d = 0xa54ff53a;
u_int32_t e = 0x510e527f;
u_int32_t f = 0x9b05688c;
u_int32_t g = 0x1f83d9ab;
u_int32_t h = 0x5be0cd19;

u_int32_t k0 = 0x428a2f98;
u_int32_t k1 = 0x71374491;
u_int32_t k2 = 0xb5c0fbcf;
u_int32_t k3 = 0xe9b5dba5;
u_int32_t k4 = 0x3956c25b;
u_int32_t k5 = 0x59f111f1;
u_int32_t k6 = 0x923f82a4;
u_int32_t k7 = 0xab1c5ed5;
u_int32_t k8 = 0xd807aa98;
u_int32_t k9 = 0x12835b01;
u_int32_t k10 = 0x243185be;
u_int32_t k11 = 0x550c7dc3;
u_int32_t k12 = 0x72be5d74;
u_int32_t k13 = 0x80deb1fe;
u_int32_t k14 = 0x9bdc06a7;
u_int32_t k15 = 0xc19bf174;
u_int32_t k16 = 0xe49b69c1;
u_int32_t k17 = 0xefbe4786;
u_int32_t k18 = 0x0fc19dc6;
u_int32_t k19 = 0x240ca1cc;
u_int32_t k20 = 0x2de92c6f;
u_int32_t k21 = 0x4a7484aa;
u_int32_t k22 = 0x5cb0a9dc;
u_int32_t k23 = 0x76f988da;
u_int32_t k24 = 0x983e5152;
u_int32_t k25 = 0xa831c66d;
u_int32_t k26 = 0xb00327c8;
u_int32_t k27 = 0xbf597fc7;
u_int32_t k28 = 0xc6e00bf3;
u_int32_t k29 = 0xd5a79147;
u_int32_t k30 = 0x06ca6351;
u_int32_t k31 = 0x14292967;
u_int32_t k32 = 0x27b70a85;
u_int32_t k33 = 0x2e1b2138;
u_int32_t k34 = 0x4d2c6dfc;
u_int32_t k35 = 0x53380d13;
u_int32_t k36 = 0x650a7354;
u_int32_t k37 = 0x766a0abb;
u_int32_t k38 = 0x81c2c92e;
u_int32_t k39 = 0x92722c85;
u_int32_t k40 = 0xa2bfe8a1;
u_int32_t k41 = 0xa81a664b;
u_int32_t k42 = 0xc24b8b70;
u_int32_t k43 = 0xc76c51a3;
u_int32_t k44 = 0xd192e819;
u_int32_t k45 = 0xd6990624;
u_int32_t k46 = 0xf40e3585;
u_int32_t k47 = 0x106aa070;
u_int32_t k48 = 0x19a4c116;
u_int32_t k49 = 0x1e376c08;
u_int32_t k50 = 0x2748774c;
u_int32_t k51 = 0x34b0bcb5;
u_int32_t k52 = 0x391c0cb3;
u_int32_t k53 = 0x4ed8aa4a;
u_int32_t k54 = 0x5b9cca4f;
u_int32_t k55 = 0x682e6ff3;
u_int32_t k56 = 0x748f82ee;
u_int32_t k57 = 0x78a5636f;
u_int32_t k58 = 0x84c87814;
u_int32_t k59 = 0x8cc70208;
u_int32_t k60 = 0x90befffa;
u_int32_t k61 = 0xa4506ceb;
u_int32_t k62 = 0xbef9a3f7;
u_int32_t k63 = 0xc67178f2;

u_int32_t k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

/*
 * function that takes a 32-bit number and right shifts it by n
 * initially shifts the bits right
 * then shifts left by 32 - n to ensure the ones at the end are rotated to the beginning
 * xor at the end to combine the right and left
*/

void compute_hash(bitset<32> W[], u_int32_t hArr[]){
    for (int t = 0; t < 64; t++){
        uint32_t T1 = (h + big_sigma_one(e) + choose(e, f, g) + k[t] + W[t].to_ulong()) % 4294967296;
        uint32_t T2 = (big_sigma_zero(a) + majority(a, b, c)) % 4294967296;
        h = g;
        g = f;
        f = e;
        e = (d + T1) % 4294967296;
        d = c;
        c = b;
        b = a;
        a = (T1 + T2) % 4294967296;
    }

    hArr[0] += a;
    hArr[1] += b;
    hArr[2] += c;
    hArr[3] += d;
    hArr[4] += e;
    hArr[5] += f;
    hArr[6] += g;
    hArr[7] += h;

}

bitset<32> right_rotation(bitset<32> bits, int n){
    try {
        if (n <= 32) {
            bitset<32> shiftedBits = bits >> n;
            bitset<32> rotatedBits = bits << 32 - n;
            return shiftedBits ^ rotatedBits;
        } else
            throw (n);


    }
    catch (int n){
        cout << "Number must be smaller than 32. Number provided: " << n << endl;
    }
}

void prepare_message_schedule(bitset<32> schedule[], bitset<32> paddedBits[]){
    for (int i = 0; i < 16; i++){
        schedule[i] = paddedBits[i];
    }
    build_message_schedule(schedule);
}

// The formula to derive any value for W at position T
void build_message_schedule(bitset<32> W[]){
    for (int t = 16; t <= 63; t++){
        W[t] = sigma_one(W[t - 2]) + (W[t - 7]).to_ulong() + sigma_zero(W[t - 15]) + (W[t-16]).to_ulong();
    }
}

ulong sigma_zero(bitset<32> bits){
    ulong sigmaReturn = (right_rotation(bits, 7)).to_ulong() ^ (right_rotation(bits, 18)).to_ulong() ^ (bits >> 3).to_ulong();
    return sigmaReturn;
}

ulong sigma_one(bitset<32> bits){
    ulong sigmaReturn = (right_rotation(bits, 17)).to_ulong() ^ (right_rotation(bits, 19)).to_ulong() ^ (bits >> 10).to_ulong();
    return sigmaReturn;
}

ulong big_sigma_zero(bitset<32> bits){
    ulong sigmaReturn = (right_rotation(bits, 2)).to_ulong() ^ (right_rotation(bits, 13)).to_ulong() ^ (right_rotation(bits, 22)).to_ulong();
    return sigmaReturn;
}

ulong big_sigma_one(bitset<32> bits){
    ulong sigmaReturn = (right_rotation(bits, 6)).to_ulong() ^ (right_rotation(bits, 11)).to_ulong() ^ (right_rotation(bits, 25)).to_ulong();
    return sigmaReturn;
}

ulong choose(bitset<32> x, bitset<32> y, bitset<32> z){
    bitset<32> chooseReturn = (x & y) ^ (~x & z);
    return chooseReturn.to_ulong();
}

ulong majority(bitset<32> x, bitset<32> y, bitset<32> z){
    bitset<32> majorityReturn = (x & y) ^ (x & z) ^ (y & z);
    return majorityReturn.to_ulong();
}
