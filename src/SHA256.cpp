//
// Created by ross on 27/10/23.
//

#include "SHA256.h"

int main(){
    string str = "She sells seashells on the seashore";
    bitset<8> bits[35];
    bitset<32> paddedBits[16];

    string_to_binary(str, bits);

    /*for (int i = 0; i < str.length(); i++){
        cout<<bits[i] << " ";
    }*/

    pad_binary(paddedBits, bits, sizeof(bits));

    /*cout<< endl <<paddedBits[0] << endl;
    cout<<paddedBits[1] << endl;
    cout<<paddedBits[2] << endl;
    cout<<paddedBits[3] << endl;*/

    add_length(paddedBits, sizeof (bits));

    for (bitset<32> p : paddedBits){
        cout<< p << endl;
    }
}