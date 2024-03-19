#include <fstream>
#include <iostream>
#include <string>

using std::string;

int *getPositions(string *strArr, int strArrSize) {
  printf("%d ", strArrSize);

  int *positions = (int *)malloc(sizeof(int) * (strArrSize + 1));

  positions[0] = 0;
  printf("%d ", positions[0]);
  positions[1] = strArr[0].length();
  printf("%d ", positions[1]);

  for (int i = 1; i < strArrSize; i++) {
    positions[i + 1] = strArr[i].length() + positions[i];
    printf("%d ", positions[0]);
  }

  return positions;
}

int main() {
  int strArrSize = 1024;
  string strArr[1024];
  int index = 0;
  string password;

  std::ifstream dictionary("dictionary.txt");

  while (getline(dictionary, password)) {
    strArr[index] = password;
    index++;
  }

  int *positions = getPositions(strArr, strArrSize);

  for (int i = 0; i < 1024; i++) {
    std::cout << positions[i] << std::endl;
  }
}
