cmake_minimum_required(VERSION 3.26)
project(gps)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
    gps.cpp
    main.cpp
    serial/serialib.cpp
    )

set(HEADERS
    gps.h
    serial/serialib.h
    )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})