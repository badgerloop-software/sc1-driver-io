project(DriversLib VERSION 0.1 LANGUAGES CXX)

add_library(drivers src/i2c.cpp src/serial.cpp src/analog.cpp)

target_include_directories(drivers PUBLIC include)

export(TARGETS drivers FILE DriversConfig.cmake)
