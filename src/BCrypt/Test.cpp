#include "Blowfish.h"
#include <cstdint>
#include <cstdio>
#include <ios>
#include <iostream>
#include <iterator>

int main() {
  uint64_t string = 0xfe45fac4fe45fac4;
  Converter converter;
  std::string output = converter.uint64_tToString(string);

  printf("%s", output.c_str());
}
