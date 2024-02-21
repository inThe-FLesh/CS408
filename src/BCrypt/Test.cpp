#include <cstdint>
#include <ios>
#include <iostream>
#include <iterator>

int main() {
  uint32_t output;
  uint64_t divider = 0xffffffff00000000;
  uint64_t block = 0xf1f1f1f1a4a4a4a4;

  output = (divider & block) >> 32;
  output = (divider >> 32) & block;
}
