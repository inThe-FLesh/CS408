#include "SHA256-Cuda.cuh"
#include <cstdio>
#include <cstring>
#include <string>

__global__ void testKernel(char *strArr, int *positions) {
  char *str = strArr;
  int start = positions[0];
  int end = positions[1];

  printf("%s %d %d\n", str, start, end);

  char *newStr = getString(str, positions, 0);

  printf("%s\n ", newStr);
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
  std::string str =
      "RedBlockBlueRedBlockBlueRedBlockBlueRedBlockBlueRedBlockBlue";
  size_t cStrSize = sizeof(char) * str.length();
  char *cStr = (char *)malloc(cStrSize), *d_cStr;

  std::strcpy(cStr, str.c_str());

  int *h_positions = (int *)malloc(sizeof(int) * 2), *d_positions;
  h_positions[0] = 0;
  h_positions[1] = 5;

  cudaMalloc(&d_cStr, cStrSize);
  cudaMalloc(&d_positions, sizeof(int) * 2);

  cudaMemcpy(d_cStr, cStr, cStrSize, cudaMemcpyHostToDevice);
  cudaMemcpy(d_positions, h_positions, sizeof(int) * 2, cudaMemcpyHostToDevice);

  testKernel<<<1, 5>>>(d_cStr, d_positions);
  cudaDeviceSynchronize();
}
