#include <bitset>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sys/types.h>

using std::bitset;
using std::cout;
using std::endl;
using std::string;
using namespace std::chrono;
using namespace std::chrono_literals;
using std::cin;
using std::cout;
using std::dec;
using std::hex;
using std::setfill;
using std::setw;
using std::string;

struct cudaStrArr {
  char *strArr;
  int *positions;
};

char *createCharArr(string *strArr, int strArrSize) {
  string output;

  for (int i = 0; i < strArrSize; i++) {
    output += strArr[i];
  }

  char *outputChar = (char *)malloc(sizeof(char) * (output.length() + 1));
  strcpy(outputChar, output.c_str());

  return outputChar;
}

int *getPositions(string *strArr, int strArrSize) {
  int *positions = (int *)malloc(sizeof(int) * (strArrSize * 2));

  positions[0] = 0;
  positions[1] = strArr[0].length();

  for (int i = 1; i < strArrSize; i++) {
    positions[i + 1] = strArr[i].length();
  }

  return positions;
}

char *getString(char *str, int *positions, int index) {
  int position = positions[index];
  int length = (positions[index + 1] - position);
  char *outputStr = (char *)malloc(sizeof(char) * length);

  for (int i = position, j = 0; i < length; i++, j++) {
    // using i and j here as the output string has to start at 0
    // and str has to start from position
    outputStr[j] = str[i];
  }
  return outputStr;
}

int main() {
  string strArr[] = {"hello", "goodbye", "nice to meet you"};
  cout << createCharArr(strArr, size(strArr)) << endl;

  cudaStrArr cStrArr;
  cStrArr.strArr = createCharArr(strArr, size(strArr));
  cStrArr.positions = getPositions(strArr, size(strArr));

  char *charStr = getString(cStrArr.strArr, cStrArr.positions, 0);
  cout << charStr << endl;
}
