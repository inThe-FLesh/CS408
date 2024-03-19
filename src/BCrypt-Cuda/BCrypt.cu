#include "BCrypt.cuh"
#include <cstring>

std::string concatenateHash(int cost, uint8_t *salt, uint64_t *ciphers) {
  Converter converter;
  std::string alg = "$2a";
  std::string costString = "$" + std::to_string(cost);
  std::string saltString((char *)salt);
  std::string cipherString;

  for (int i = 0; i < 3; i++) {
    uint8_t *cipher = converter.bits_to_bytes(ciphers[i], 64);
    std::string str((char *)cipher);
    cipherString += str;
  }

  cipherString = cipherString.substr(0, 23);

  saltString = base64_encode(saltString);
  cipherString = base64_encode(cipherString);

  std::string output = alg + costString + saltString + cipherString;

  return output;
}

uint8_t *appendRoundText(uint8_t **roundText, int numWords) {
  uint8_t *appended = (uint8_t *)malloc(sizeof(uint8_t) * (numWords * 8));

  for (int i = 0; i < 3; i++) {
    for (int n = 0; n < 8; n++) {
      appended[n + (8 * i)] = roundText[i][n];
    }
  }

  return appended;
}

int BCrypt(int cost, uint8_t *salt, uint8_t *password, int passwordLength) {
  uint32_t *P;
  uint32_t **S;
  uint8_t *saltBackup = (uint8_t *)malloc(sizeof(uint8_t) * 16);

  memcpy(saltBackup, salt, sizeof(uint8_t) * 16);

  uint8_t cipherText[24] = {'O', 'r', 'p', 'h', 'e', 'a', 'n', 'B',
                            'e', 'h', 'o', 'l', 'd', 'e', 'r', 'S',
                            'c', 'r', 'y', 'D', 'o', 'u', 'b', 't'};
  uint8_t **roundText;

  EksBlowfish eks(cost, passwordLength, salt, password);

  eks.generate_keys();

  // expensive key setup
  P = eks.getP();
  S = eks.getS();

  Blowfish blowfishInit(P, S, cipherText, 24);
  roundText = blowfishInit.Encrypt();

  for (int i = 0; i < 63; i++) {
    Blowfish blowfish(P, S, appendRoundText(roundText, 3), 24);
    roundText = blowfish.Encrypt();
  }

  Converter converter;
  uint64_t *ciphers = (uint64_t *)malloc(sizeof(uint64_t) * 3);
  for (int i = 0; i < 3; i++) {
    ciphers[i] = converter.bytes_to_64bit(roundText[i], 8);
  }

  std::string hash = concatenateHash(cost, saltBackup, ciphers);

  cout << std::hex << hash << endl;

  return 0;
}

int main() {
  int cost = 4;
  int passwordLength = 9;
  uint8_t salt[16] = {0x47, 0xD8, 0x7F, 0x70, 0x83, 0xF3, 0xD2, 0x08,
                      0xBE, 0x51, 0x13, 0x4D, 0x5F, 0x79, 0x21, 0xD8};
  uint8_t password[9] = {'a', 'b', 'c', '1', '2', '3', 'x', 'y', 'z'};

  struct timeval start, end;

  // Timer code adapted from
  // https://www.geeksforgeeks.org/measure-execution-time-with-high-precision-in-c-c/
  // start timer.
  gettimeofday(&start, NULL);

  // unsync the I/O of C and C++.
  std::ios_base::sync_with_stdio(false);

  BCrypt(cost, salt, password, passwordLength);

  gettimeofday(&end, NULL);

  double time_taken;

  time_taken = (end.tv_sec - start.tv_sec) * 1e6;
  time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;

  cout << "Time taken by program is : " << std::fixed << time_taken
       << std::setprecision(6);
  cout << " sec" << endl;

  double hashesPerSec = 0;

  if (time_taken < 1.0) {
    hashesPerSec = 60.0 / time_taken;
  } else {
    hashesPerSec = time_taken / 60;
  }
  cout << "Hashes per second: " << hashesPerSec << endl;
}
