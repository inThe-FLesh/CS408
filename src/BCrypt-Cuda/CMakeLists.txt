cmake_minimum_required(VERSION 3.26)
project(BCrypt-Cuda CUDA)

set(CMAKE_CUDA_STANDARD 17)

add_executable(BCrypt-Cuda
        BCrypt.cu
        BCrypt.cuh
        base64.cu
        base64.cuh
        Blowfish.cuh
        converter.cuh
        EksBlowfish.cuh
)

add_compile_options(-G)

set_target_properties(BCrypt-Cuda PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
