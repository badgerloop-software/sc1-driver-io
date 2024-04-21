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
        backend/backendProcesses.cpp
        main.cpp
        DataProcessor/dataUnpacker.cpp
        backend/dataFetcher.cpp
        backend/telemetrylib/tcp.cpp
        backend/telemetrylib/telemetry.cpp
        backend/telemetrylib/sql.cpp
        gps/gps.cpp
        3rdparty/serial/serialib.cpp
        )

# Add the header files
set(HEADERS
        ${HEADERS}
        DataProcessor/dataUnpacker.h
        backend/dataFetcher.h
        backend/backendProcesses.h
        backend/telemetrylib/telemetry.h
        backend/telemetrylib/DTI.h
        gps/gps.h
        3rdparty/serial/serialib.h
        )

# Add the resource files
qt_add_resources(RESOURCES
        UI/Items/qml.qrc
        UI/Images/images.qrc
        UI/fonts/fonts.qrc
        )

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

# Link against the required Qt modules
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
target_include_directories(${PROJECT_NAME} PRIVATE ./)
