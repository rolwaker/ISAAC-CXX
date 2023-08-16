cmake_minimum_required(VERSION 3.0)

project(ISAAC32 C CXX)

add_executable(isaac32-old
    old/src/rand.c
)

target_include_directories(isaac32-old PRIVATE old/include)

add_executable(isaac32-new
    new/src/isaac32.cpp
    new/src/main.cpp
)

target_include_directories(isaac32-new PRIVATE new/include)
