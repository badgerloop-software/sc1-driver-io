set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

configure_file(config.h.in config.h)

cmake_minimum_required(VERSION 3.5)
project(solar-car-dashboard)

# Find the required Qt packages
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
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
        telemetrylib/TCP.cpp
        telemetrylib/Telemetry.cpp
        telemetrylib/SQL.cpp
        telemetrylib/DataResend.cpp
        )

# Add the header files
set(HEADERS
        ${HEADERS}
        DataProcessor/DataUnpacker.h
        backendprocesses.h
        telemetrylib/Telemetry.h
        telemetrylib/DTI.h
        telemetrylib/DataResend.h
        )

# Check if FIRMWARE flag is set to ON
if(FIRMWARE)
    message(----------FIRMWAREBUILD----------)
    set(FIRMWARE_BUILD ON) # set config.h to define FIRMWARE_BUILD
    # Add the sources in the embedded folder
    set(SOURCES
            ${SOURCES}
            embedded/drivers/src/i2c.cpp
            embedded/drivers/src/serial.cpp
            embedded/drivers/src/gpio.cpp
            embedded/devices/src/ads1219.cpp
            embedded/devices/src/ina3221.cpp
            embedded/devices/src/tca6416.cpp
            )

    set(HEADERS
            ${HEADERS}
            embedded/drivers/include/i2c.h
            embedded/drivers/include/i2c-dev.h
            embedded/drivers/include/serial.h
            embedded/drivers/include/gpio.h
            embedded/devices/include/ads1219.h
            embedded/devices/include/ina3221.h
            embedded/devices/include/tca6416.h
            embedded/controlsWrapper.h
            )
#if not firmware build...
else()
    message(----------SOFTWAREBUILD----------)
    set(FIRMWARE_BUILD ON) # set config.h to define FIRMWARE_BUILD
    set(SOURCES
            ${SOURCES}
            DataProcessor/DataGen.cpp
            )

    set(HEADERS
            ${HEADERS}
            DataProcessor/DataGen.h
            )
endif()

# Add the resource files
qt6_add_resources(RESOURCES
        qml.qrc
        UI/Images/images.qrc
        UI/fonts/fonts.qrc
        )

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES})

# Link against the required Qt modules
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)
target_include_directories(${PROJECT_NAME} PRIVATE ./)