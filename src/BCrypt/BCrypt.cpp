#include "BCrypt.h"

int main() {
  int cost = 12;
  uint32_t *P;
  uint32_t **S;
  std::string hash;
  uint64_t *encryptedText;
  char password[] = "abc123xyz";
  std::tuple<uint32_t *, uint32_t **> PsAndS;
  std::string cipherText = "OrpheanBeholderScryDoubt";
  uint64_t salt[2] = {0xD4697991E1BB7BD1, 0x26E8163EDB3FD594};

  PsAndS = EksBlowfishSetup(cost, salt, password);

  P = std::get<0>(PsAndS);
  S = std::get<1>(PsAndS);

  for (int i = 0; i < 64; i++) {
    Blowfish blowfish(P, S, cipherText);
    encryptedText = blowfish.EncryptECB();
  }

  free(P);
  free(S);

  cipherText =
      generateCipherString(encryptedText, (cipherText.length() * 8) / 64);

  std::string output = concatenate(cost, salt, cipherText);

  std::cout << output << std::endl;

  return 0;
}

std::string generateCipherString(uint64_t *cipher, int cipherArrLength) {
  const uint8_t divider = 0xff;
  std::string output = "";
  Converter converter;

  for (int i = 0; i < cipherArrLength; i++) {
    output += converter.uint64_tToString(cipher[i]);
  }

  return output;
}

std::string concatenate(int cost, uint64_t *salt, std::string cipher) {
  std::string costString = std::to_string(cost);
  std::string saltString = std::to_string(salt[0]) + std::to_string(salt[1]);
  std::string outputString = "$2a$" + costString + saltString + cipher;

  return outputString;
}
