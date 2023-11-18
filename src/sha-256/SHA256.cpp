//
// Created by ross on 27/10/23.
//

#include "SHA256.h"

int main(){
    string str = "";
    cout << "Enter String: ";
    cin >> str;
    bitset<8> bits[str.size()];
    bitset<32> paddedBits[16];


    uint32_t hArr[] =
            {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
             0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

    string_to_binary(str, bits);

    for (int i = 0; i < str.length(); i++){
        cout<<bits[i] << " ";
    }

    pad_binary(paddedBits, bits, sizeof(bits));

    cout << endl << "Padded Bits" << endl;

    for (bitset<32> p : paddedBits){
        cout<< p << endl;
    }

    add_length_bits(paddedBits, sizeof (bits));

    cout << "Length Bits" << endl;

    for (bitset<32> p : paddedBits){
        cout<< p << endl;
    }

    bitset<32> schedule[64];

    prepare_message_schedule(schedule, paddedBits);

    compute_hash(schedule, hArr);

    cout << "hash" << endl;

    for (ulong h : hArr){
        cout << setfill('0') << hex << setw(8) << h;
    }

  cout << endl;
}
