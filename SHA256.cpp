//
// Created by ross on 27/10/23.
//

#include "SHA256.h"

void string_to_binary(const string& str, bitset<8> bits[]){
    // breaks up each word in the string to an 8-bit binary number and adds them to  the array
    for(int i = 0; i < str.length(); i++){
        bits[i] =  bitset<8>(str[i]);
    }
}

void pad_binary(bitset<32> paddedBits[], bitset<8> bits[], int size){
    // dividing by 8 to get the number of 8 bit chunks
    int index = (int) size / 8;
    index = index/4;
    int remainder = index % 4;

    for (int i = 0, j = 0; j < index; i+=4, j++){
        // multiply each by 2^n to move the binary number n places to the left
        paddedBits[j] = bitset<32>(bits[i].to_ullong() * pow(2, 24) + bits[i+1].to_ullong() * pow(2, 16) + bits[i+2].to_ullong() * pow(2, 8) + bits[i+3].to_ullong());
    }
}

int main(){
    string str = "RedBlockBlue";
    bitset<8> bits[12];
    bitset<32> paddedBits[16];

    string_to_binary(str, bits);

    /*for (int i = 0; i < str.length(); i++){
        cout<<bits[i] << " ";
    }*/

    pad_binary(paddedBits, bits, sizeof(bits));

    cout<<paddedBits[0] << endl;
    cout<<paddedBits[1] << endl;
    cout<<paddedBits[2] << endl;
}