//
// Created by ross on 27/10/23.
//

#include "computation.cuh"
#include "sha256Cuda.cuh"

void sha(string *strArr) {

  // defining 2D arrays using malloc
  bitset<32>(*schedules)[64] =
      (bitset<32>(*)[64])malloc(sizeof(bitset<32>[64][64]));

  uint32_t(*hArrs)[64] = (uint32_t(*)[64])malloc(sizeof(uint32_t[8][64]));

  for (int i = 0; i < 64; i++) {
    string str = strArr[i];

    bitset<8> bits[str.size()];
    bitset<32> paddedBits[16];

    uint32_t hArr[] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                       0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

    for (int j = 0; j < 8; j++) {
      hArrs[j][i] = hArr[j];
    }

    string_to_binary(str, bits);

    pad_binary(paddedBits, bits, sizeof(bits));

    /*for (bitset<32> pad : paddedBits){
        cout << pad << endl;
    }*/

    add_length_bits(paddedBits, sizeof(bits));

    bitset<32> schedule[64];

    prepare_message_schedule(schedule, paddedBits);

    for (int j = 0; j < 64; j++) {
      schedules[j][i] = hArr[j];
    }
  }

  /*for (ulong h : hArr) {
    cout << setfill('0') << hex << setw(8) << h;
  }

  cout << endl;*/
}

int main() {
  string *strArr = (string *)malloc(sizeof(string) * 64);
  int count = 0;

  // solution for timer found on stack overflow
  auto now = std::chrono::steady_clock::now;
  duration<long> executeTime = 1s;
  auto start = now();

  while ((now() - start) < executeTime) {
  }

  cout << "Hashes per second: " << dec << count << endl;
}
