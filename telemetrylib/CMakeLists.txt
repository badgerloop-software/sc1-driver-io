set(CMAKE_AUTOMOC ON)

cmake_minimum_required(VERSION 3.20)
project(telemetrylib)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(ZLIB REQUIRED)
add_library(telemetrylib SHARED Telemetry.cpp DTI.h TCP.cpp SQL.cpp DataResend.cpp DataResend.h)

target_link_libraries(telemetrylib PRIVATE Qt6::Network)

