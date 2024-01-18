//
// Created by ross on 27/10/23.
//

#include "SHA256.h"

void sha(string str) {
  bitset<8> bits[str.size()];
  bitset<32> paddedBits[16];

  uint32_t hArr[] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                     0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

  string_to_binary(str, bits);

  pad_binary(paddedBits, bits, sizeof(bits));

  /*for (bitset<32> pad : paddedBits){
      cout << pad << endl;
  }*/

  add_length_bits(paddedBits, sizeof(bits));

  bitset<32> schedule[64];

  prepare_message_schedule(schedule, paddedBits);

  compute_hash(schedule, hArr);

  for (ulong h : hArr) {
<<<<<<< HEAD
    cout << setfill('0') << hex << setw(8) << h;
=======
      cout << setfill('0') << hex << setw(8) << h;
>>>>>>> refs/remotes/origin/dev
  }

  cout << endl;
}

int main() {
  string strArr[] = {"RedBlockBlue", "12345", "zorgLover123"};
<<<<<<< HEAD
  int count = 0;
=======
  //int count = 0;
>>>>>>> refs/remotes/origin/dev

  // solution for timer found on stack overflow
  /*auto now = std::chrono::steady_clock::now;
  duration<long> executeTime = 1s;
  auto start = now();

  while ((now() - start) < executeTime) {
    for (string str : strArr) {
      sha(str);
      count += 1;
    }
  }

  cout << "Hashes per second: " << dec << count << endl;*/
  sha(strArr[0]);
}
