cmake_minimum_required(VERSION 3.26)
project(CS408)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS408
        src/sha-256/SHA256.cpp
        src/sha-256/SHA256.h
        src/sha-256/preprocessing.cpp
        src/sha-256/computation.h
        src/sha-256/computation.cpp)
