nvcc -gencode arch=compute_75,code=sm_75 -rdc=true SHA256-Cuda.cu -o main 
./main
