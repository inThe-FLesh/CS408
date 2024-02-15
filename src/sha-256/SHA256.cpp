//
// Created by ross on 27/10/23.
//
//
// upgraded implementation to no longer use bitset and use malloc to declare
// arrays. All arrays are now passed as pointers for efficiency

#include "SHA256.h"
#include "computation.h"
#include <cstdlib>

void sha(string str) {
  uint8_t *bits;
  uint32_t *paddedBits;
  int bitSize = 0;

  uint32_t hArr[] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                     0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

  bits = string_to_binary(str);

  cout << "bits: ";

  for (int i = 0; i < str.length(); i++) {
    cout << bits[i] << " ";
  }

  cout << endl;

  paddedBits = pad_binary(bits, str.size());

  cout << "Padded Bits: ";

  for (int i = 0; i < 16; i++) {
    cout << hex << paddedBits[i] << " ";
  }

  cout << endl;

  add_length_bits(paddedBits, (str.size() * 8));

  cout << "Length Bits: ";

  for (int i = 0; i < 16; i++) {
    cout << paddedBits[i];
  }

  cout << endl;

  uint32_t *schedule;

  schedule = prepare_message_schedule(paddedBits);

  cout << "Message Schedule: ";

  for (int i = 0; i < 16; i++) {
    cout << schedule[i];
  }

  cout << endl;

  compute_hash(schedule, hArr);

  cout << "hash: ";

  for (uint32_t h : hArr) {
    cout << setfill('0') << hex << setw(8) << h;
    cout << setfill('0') << hex << setw(8) << h;
  }

  cout << endl;

  free(paddedBits);
  free(bits);
  free(schedule);
}

int main() {
  string strArr[] = {"RedBlockBlue", "12345", "zorgLover123"};
  int count = 0;
  // solution for timer found on stack overflow
  /*auto now = std::chrono::steady_clock::now;
  duration<long> executeTime = 1s;
  auto start = now();

  while ((now() - start) < executeTime) {
    for (string str : strArr) {
      sha(str);
      count += 1;
    }
  }*/

  // cout << "Hashes per second: " << dec << count << endl;
  sha(strArr[0]);
}
