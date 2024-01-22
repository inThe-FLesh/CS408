nvcc SHA256-Cuda.cu -gencode arch=compute_75,code=sm_75 -dc -o SHA256-Cuda.o
nvcc preprocessing.cu -gencode arch=compute_75,code=sm_75 -dc -o preprocessing.o
nvcc computation.cu -gencode arch=compute_75,code=sm_75 -dc -o computation.o
nvcc -gencode arch=compute_75,code=sm_75 SHA256-Cuda.o preprocessing.o computation.o -o mainCuda
