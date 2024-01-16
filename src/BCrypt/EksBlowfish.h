#include <cstdint>

void initialiseState(uint32_t *P, uint32_t *S);

uint32_t **EksBlowfishSetup(int cost, uint64_t *salt, char *password);
