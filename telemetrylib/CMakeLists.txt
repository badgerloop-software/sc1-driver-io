cmake_minimum_required(VERSION 3.20)
project(telemetrylib)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt6 REQUIRED COMPONENTS Network)

add_library(telemetrylib SHARED library.cpp DTI.h TCP.cpp)

target_link_libraries(telemetrylib PRIVATE Qt6::Network)
