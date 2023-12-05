cmake_minimum_required(VERSION 3.26)
project(sha_256_cuda CUDA)

set(CMAKE_CUDA_STANDARD 17)

add_executable(sha_256_cuda src/sha256Cuda.cu
        src/computation.cu
        src/preprocessing.cu
        ../sha-256/preprocessing.h
        ../sha-256/preprocessing.h
        ../sha-256/preprocessing.h)

set_target_properties(sha_256_cuda PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
