cmake_minimum_required(VERSION 3.0)

project(ISAAC64 C CXX)

add_executable(isaac64-old
    old/src/isaac64.c
)

target_include_directories(isaac64-old PRIVATE old/include)

add_executable(isaac64-new
    new/src/isaac64.cpp
    new/src/main.cpp
)

target_include_directories(isaac64-new PRIVATE new/include)
