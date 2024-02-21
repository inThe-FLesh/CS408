#include "BCrypt.h"
#include <cstdint>
#include <cstdlib>
#include <string>
#include <tuple>

int main() {
  uint64_t salt[2] = {0xD4697991E1BB7BD1, 0x26E8163EDB3FD594};
  int cost;
  char password[] = "openSesame";
  std::string cipherText = "OrpheanBeholderScryDoubt";
  std::string hash;
  uint32_t *P;
  uint32_t **S;
  std::tuple<uint32_t *, uint32_t **> PsAndS;

  PsAndS = EksBlowfishSetup(cost, salt, password);

  P = std::get<0>(PsAndS);
  S = std::get<1>(PsAndS);

  for (int i = 0; i < 64; i++) {
    Blowfish blowfish(P, S, cipherText);
    cipherText = blowfish.Encrypt();
  }

  free(P);

  // freeing each of the pointers held in the SBox array before freeing the
  // array itself
  for (int i = 0; i < 4; i++) {
    free(S[i]);
  }

  free(S);

  std::string output = concatenate(cost, salt, cipherText);
}
