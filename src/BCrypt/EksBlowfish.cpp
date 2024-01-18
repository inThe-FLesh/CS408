#include "EksBlowfish.h"
#include <cstdint>
#include <cstdlib>

void initialiseState(uint32_t *P, uint32_t *S){
  
}

uint32_t **EksBlowfishSetup(int cost, uint64_t *salt, char *password){
  uint32_t *P = (uint32_t *) malloc(sizeof(uint32_t) * 18);
  uint32_t *S = (uint32_t *) malloc(sizeof(uint32_t) * 256);
  uint32_t **out = (uint32_t **)malloc(sizeof(uint32_t *) * 2);

  

  out[0] = P;
  out[1] = S;

  return out;
}
