cmake_minimum_required(VERSION 3.20)
project(DataGenerator)

set(CMAKE_CXX_STANDARD 14)

add_executable(DataGenerator main.cpp dataGen.cpp dataGen.h)
