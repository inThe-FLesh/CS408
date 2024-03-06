#include "BCrypt.h"
#include "base64.h"
#include <cstdint>
int BCrypt(int cost, uint8_t *salt, uint8_t *password, int passwordLength) {
  uint32_t *P;
  uint32_t **S;
  uint8_t cipherText[24] = {'O', 'r', 'p', 'h', 'e', 'a', 'n', 'B',
                            'e', 'h', 'o', 'l', 'd', 'e', 'r', 'S',
                            'c', 'r', 'y', 'D', 'o', 'u', 'b', 't'};
  uint8_t *roundText;

  EksBlowfish eks(cost, passwordLength, salt, password);

  eks.generate_keys();

  P = eks.getP();
  S = eks.getS();

  Blowfish blowfishInit(P, S, cipherText, 24);
  roundText = blowfishInit.Encrypt();

  for (int i = 0; i < 63; i++) {
    Blowfish blowfish(P, S, roundText, 8);
    roundText = blowfish.Encrypt();
  }

  return 0;
}

int main() {
  int cost = 3;
  int passwordLength = 12;
  uint8_t salt[16] = {0xF7, 0x8E, 0x2D, 0x6B, 0xC3, 0x9A, 0x1F, 0x5D,
                      0xA9, 0x0E, 0x73, 0xB8, 0x64, 0xEC, 0x21};
  uint8_t password[12] = {'R', 'e', 'd', 'B', 'l', 'o',
                          'c', 'k', 'B', 'l', 'u', 'e'};

  BCrypt(cost, salt, password, passwordLength);
}
