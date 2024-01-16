#include "BCrypt.h"
#include <cstdint>
#include <cstdlib>
#include <string>

int main(){
  uint64_t salt[2] = {0xD4697991E1BB7BD1, 0x26E8163EDB3FD594};
  int cost;
  char password[] = "openSesame";
  std::string cipherText = "OrpheanBeholderScryDoubt";
  std::string hash; 
  uint32_t *P;
  uint32_t *S;
  uint32_t **PsAndS;
  
PsAndS = EksBlowfishSetup(cost, salt, password);
  
  P = PsAndS[0];
  S = PsAndS[1];

  free(PsAndS);
  
  for(int i = 0; i < 64; i++){
    cipherText = EncryptECB(P, S, cipherText);
  }

  free(P);
  free(S);

  std::string output = concatenate(cost, salt, hash);
}
