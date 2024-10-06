set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

cmake_minimum_required(VERSION 3.5)
project(solar-car-dashboard)

# Find the required Qt packages
find_package(QT NAMES Qt5 Qt6 COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

message(----------QT-VERSION:${QT_VERSION_MAJOR}-----------)
# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Add shared sources to build
set(SOURCES
        ${SOURCES}
        backendprocesses.cpp
        main.cpp
        DataProcessor/DataUnpacker.cpp
        DataProcessor/datafetcher.cpp
        telemetrylib/TCP.cpp
        telemetrylib/Telemetry.cpp
        telemetrylib/SQL.cpp
        gps/gps.cpp
        3rdparty/serial/serialib.cpp
        Config.cpp
        )

# Add the header files
set(HEADERS
        ${HEADERS}
        DataProcessor/DataUnpacker.h
        DataProcessor/datafetcher.h
        backendprocesses.h
        telemetrylib/Telemetry.h
        telemetrylib/DTI.h
        gps/gps.h
        3rdparty/serial/serialib.h
        Config.h
        )

# Add the resource files
qt_add_resources(RESOURCES
        qml.qrc
        UI/Images/images.qrc
        UI/fonts/fonts.qrc
        )

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

# Link against the required Qt modules
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
target_include_directories(${PROJECT_NAME} PRIVATE ./)
