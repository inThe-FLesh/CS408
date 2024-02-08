#include "EksBlowfish.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>

// The cyclePassword function is used to get 32 bits of characters
// and record the last position they were taken from.
// This allows expandKey to treat the password cyclically.

std::tuple<string, int> cyclePassword(string password, int position) {
  string output;

  if ((position + 4) < password.length()) {
    output.append(password.begin() + position,
                  password.begin() + (position + 4));
  } else {

    output.append(password.begin() + position,
                  password.begin() +
                      (position + (password.length() - position)));

    position = 0;

    output.append(password.begin() + position,
                  password.begin() + (position + (4 - output.length())));
  }

  std::tuple<string, int> outputTuple = std::make_tuple(output, position);

  return outputTuple;
}

void expandKey(uint32_t *P, uint32_t **S, string password, uint64_t *salt) {
  int position = 0;

  for (int i = 0; i < 18; i++) {
    std::tuple<string, int> cycledPass = cyclePassword(password, position);
    string passwordBits = std::get<0>(cycledPass);
    position = std::get<1>(cycledPass);
    P[i] = P[i] ^ std::stoul(passwordBits);
  }

  // continue from here
}

void initialiseState(uint32_t *P, uint32_t **S) {
  uint32_t pi = 3141592653;

  for (int i = 0; i < 18; i++) {
    P[i] = pi;
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 256; j++) {
      S[i][j] = pi;
    }
  }
}

std::tuple<uint32_t *, uint32_t **> EksBlowfishSetup(int cost, uint64_t *salt,
                                                     char *password) {

  uint32_t *P = (uint32_t *)malloc(sizeof(uint32_t) * 18);
  uint32_t *S1 = (uint32_t *)malloc(sizeof(uint32_t) * 256);
  uint32_t *S2 = (uint32_t *)malloc(sizeof(uint32_t) * 256);
  uint32_t *S3 = (uint32_t *)malloc(sizeof(uint32_t) * 256);
  uint32_t *S4 = (uint32_t *)malloc(sizeof(uint32_t) * 256);
  uint32_t **S = (uint32_t **)malloc(sizeof(uint32_t *) * 4);

  S[0] = S1;
  S[1] = S2;
  S[2] = S3;
  S[3] = S4;

  initialiseState(P, S);

  std::tuple output = std::make_tuple(P, S);

  return output;
}
