cmake_minimum_required(VERSION 3.27)
project(BCrypt)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(BCrypt
        BCrypt.cpp
        BCrypt.h
        Blowfish.h
        EksBlowfish.h
        base64.cpp
        base64.h
        converter.h
        test.cpp
)
