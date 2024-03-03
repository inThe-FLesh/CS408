#include "EksBlowfish.h"
#include <ios>
#include <iostream>
#include <ostream>

void printCycle(uint32_t cycle) { std::cout << std::hex << cycle << std::endl; }

int main() {
  uint8_t salt[16] = {};
  uint8_t password[4] = {'R', 'e', 'd', 'B'};
  EksBlowfish eks(0, 4, salt, password);

  for (int i = 0; i < 4; i++) {
    std::cout << password[i];
  }

  std::cout << std::endl;

  uint32_t hexPass = 0x52656442;

  uint32_t output = eks.cyclePassword(0, 4);

  assert(output = hexPass);

  std::cout << "Test 1 passed." << std::endl;

  output = eks.cyclePassword(1, 5);

  assert(output == 0x65644252);
  std::cout << "Test 2 passed." << std::endl;

  output = eks.cyclePassword(2, 6);

  assert(output == 0x64425265);
  std::cout << "Test 3 passed." << std::endl;

  output = eks.cyclePassword(3, 7);

  assert(output == 0x42526564);
  std::cout << "Test 4 passed." << std::endl;
}
