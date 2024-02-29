#include "Blowfish.h"
#include <cstdint>
#include <cstdlib>
#include <string>
#include <tuple>

using std::string;

std::tuple<string, int> cyclePassword(string password, int position);

std::tuple<uint32_t *, uint32_t **> EksBlowfishSetup(int cost, uint64_t *salt,
                                                     char *password);

void expandKey(uint32_t *P, uint32_t **S, char *password, uint64_t *salt);

void initialiseState(uint32_t *P, uint32_t **S);
