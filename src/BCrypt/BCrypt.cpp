#include "BCrypt.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>

int main() {
  int cost = 12;
  uint32_t *P;
  uint32_t **S;
  std::string hash;
  uint64_t *encryptedText;
  char password[10] = "abc123xyz";
  std::tuple<uint32_t *, uint32_t **> PsAndS;
  std::string cipherText = "OrpheanBeholderScryDoubt";
  uint64_t salt[2] = {0x47d87f7083f3d208, 0x51134d5f7921d8};

  PsAndS = EksBlowfishSetup(cost, salt, password);

  P = std::get<0>(PsAndS);
  S = std::get<1>(PsAndS);

  for (int i = 0; i < 64; i++) {
    Blowfish blowfish(P, S, cipherText);
    encryptedText = blowfish.EncryptECB();
  }

  free(P);
  free(S);

  unsigned char **bytes = generateBytes(encryptedText);
  std::string base64Bytes = generateBase64(bytes);

  free(bytes);

  std::cout << base64Bytes << std::endl;

  return 0;
}

std::string generateBase64(unsigned char **bytes) {
  std::string output;
  for (int i = 0; i < 3; i++) {
    const unsigned char *byteArr = bytes[i];
    output += base64_encode(byteArr, sizeof(unsigned char) * 8);
  }

  return output;
}

unsigned char **generateBytes(uint64_t *encryptedText) {
  Converter converter;

  unsigned char **output =
      (unsigned char **)malloc(sizeof(unsigned char *) * 3);

  output[0] = converter.uint64_tToString(encryptedText[0]);
  output[1] = converter.uint64_tToString(encryptedText[1]);
  output[2] = converter.uint64_tToString(encryptedText[2]);

  return output;
}
