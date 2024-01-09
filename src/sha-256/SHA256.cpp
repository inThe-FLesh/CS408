//
// Created by ross on 27/10/23.
//
//
// Added testString to allow second marker to review discrete steps. This is not
// present in the dev version.

#include "SHA256.h"
#include <cstring>

void sha(string str) {
  bitset<8> bits[str.size()];
  bitset<32> paddedBits[16];

  uint32_t hArr[] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                     0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

  string_to_binary(str, bits);

  pad_binary(paddedBits, bits, sizeof(bits));

  if (str == "testString") {
    cout << "----Padded----" << endl;

    for (bitset<32> pad : paddedBits) {
      cout << pad << endl;
    }

    cout << endl;
  }

  add_length_bits(paddedBits, sizeof(bits));

  if (str == "testString") {
    cout << "----Length Bits----" << endl;
    for (bitset<32> pad : paddedBits) {
      cout << pad << endl;
    }
    cout << endl;
  }

  bitset<32> schedule[64];

  prepare_message_schedule(schedule, paddedBits);

  if (str == "testString") {
    cout << "----Message Schedule----" << endl;

    for (bitset<32> sched : schedule) {
      cout << sched << endl;
    }

    cout << endl;
  }

  compute_hash(schedule, hArr);

  if (str == "testString") {
    cout << "----Hash----" << endl;
  }

  for (ulong h : hArr) {
    cout << setfill('0') << hex << setw(8) << h;
  }

  cout << endl;
}

void timed() {
  string strArr[] = {"RedBlockBlue", "12345", "zorgLover123"};
  int count = 0;

  // solution for timer found on stack overflow
  auto now = std::chrono::steady_clock::now;
  duration<long> executeTime = 1s;
  auto start = now();

  while ((now() - start) < executeTime) {
    for (string str : strArr) {
      sha(str);
      count += 1;
    }
  }

  cout << "Hashes per second: " << dec << count << endl;
}

void test() {
  string input = "testString";
  sha(input);
}

int main(int argC, char *argV[]) {
  if (argV[1] && strcmp(argV[1], "test") == 0) {
    test();
  } else {
    timed();
  }
}
