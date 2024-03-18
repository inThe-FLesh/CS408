#include <cstdio>
#include <iostream>
__global__ void kernel() { printf("Hello from GPU!\n"); }

int main() {
  std::cout << "Hello, World!" << std::endl;
  kernel<<<1, 1>>>();
  cudaDeviceSynchronize();
  return 0;
}
