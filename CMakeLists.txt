cmake_minimum_required(VERSION 3.17)
project(TP_AAIA)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3 -lm")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O3 -lm")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -lm")

add_executable(TP_AAIA State.cpp State.h idastar.cpp)