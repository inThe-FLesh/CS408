#include "EksBlowfish.h"
#include <cstdint>
#include <cstdlib>
#include <string>
#include <sys/types.h>
#include <tuple>

std::string generateCipherString(uint64_t *cipher, int cipherArrLength);

std::string concatenate(int cost, uint64_t *salt, std::string cipher);
