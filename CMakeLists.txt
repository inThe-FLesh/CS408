cmake_minimum_required(VERSION 3.26)
project(CS408)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CS408
        SHA256.cpp
        SHA256.h)
