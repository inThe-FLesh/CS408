#include <cstdint>
#include <string>
#include <tuple>

using std::string;

std::tuple<string, int> cyclePassword(string password, int position);

void initialiseState(uint32_t *P, uint32_t **S);

std::tuple<uint32_t *, uint32_t **> EksBlowfishSetup(int cost, uint64_t *salt,
                                                     char *password);
