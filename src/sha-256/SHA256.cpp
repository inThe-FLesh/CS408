//
// Created by ross on 27/10/23.
//
//
// upgraded implementation to no longer use bitset and use malloc to declare
// arrays. All arrays are now passed as pointers for efficiency

#include "SHA256.h"
#include "computation.h"
#include <bits/stdc++.h>
#include <cstdlib>
#include <exception>
#include <ios>
#include <iostream>
#include <sys/time.h>

int sha(string str) {
  uint8_t *bits;
  uint32_t *paddedBits;
  int bitSize = 0;

  uint32_t hArr[] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                     0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

  try {

    bits = string_to_binary(str);

    paddedBits = pad_binary(bits, str.size());

    add_length_bits(paddedBits, (str.size() * 8));

    uint32_t *schedule;

    schedule = prepare_message_schedule(paddedBits);

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

  } catch (const std::exception &exception) {
    std::cerr << "Exception: " << exception.what() << endl;
    return 1;
  }

  return 0;
}

int main() {
  string strArr[] = {"RedBlockBlue", "12345", "zorgLover123"};

  struct timeval start, end;

  // Timer code adapted from
  // https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
  // start timer.
  gettimeofday(&start, NULL);

  // unsync the I/O of C and C++.
  std::ios_base::sync_with_stdio(false);

  int shaError = sha(strArr[0]);

  if (shaError == 1) {
    cout << "sha function failed" << endl;
    return 1;
  }

  gettimeofday(&end, NULL);

  double time_taken;

  time_taken = (end.tv_sec - start.tv_sec) * 1e6;
  time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

  cout << "Time taken by program is : " << std::fixed << time_taken
       << std::setprecision(6);
  cout << " sec" << endl;

  double hashesPerSec = 60.0 / time_taken;
  cout << "Hashes per second: " << hashesPerSec << endl;

  // sha(strArr[0]);
  return 0;
}
