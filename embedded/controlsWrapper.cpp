#include "embedded/controlsWrapper.h"
#include <QDebug>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <embedded/devices/include/ads1219.h>
#include <embedded/devices/src/ads1219.cpp>
#include <embedded/drivers/include/serial.h>
#include <embedded/drivers/src/serial.cpp>
#define T_MESSAGE_US 70000  // around 1/15 of a second
#define HEARTBEAT 2         // error state if this # messages that aren't read

Serial serial;
QMutex uartMutex;

#define TOTAL_BYTES 399
controlsWrapper::controlsWrapper(QByteArray &bytes, QMutex &mutex, std::atomic<bool> &restart_enable, QObject *parent) : QObject(parent), bytes(bytes), mutex(mutex), restart_enable(restart_enable) {
    //this->bytes = bytes;
    serial = Serial();
    serial.openDevice(0, 115200);
}

// This is the firmware main loop. It's called in a separate thread in DataUnpacker.cpp
// Put your testing code here!
void controlsWrapper::startThread() {
    int messages_not_received = 0;
    while(true) {
        char buffTemp[TOTAL_BYTES];
        // read
        uartMutex.lock();
        // check if we actually read a message 
        if (serial.readBytes(buffTemp, TOTAL_BYTES, T_MESSAGE_US, 0) == 0) {
            if (++messages_not_received == HEARTBEAT) {
                restart_enable = 1;
            }
        } else {
            messages_not_received = 0;
        }
        uartMutex.unlock();

        // write restart_enable signal
        uartMutex.lock();
        std::cout << "restart_enable: " << restart_enable << std::endl;
        serial.writeBytes(&restart_enable, 1); 
        uartMutex.unlock();
        
        // copy data in char array to QByteArray
        mutex.lock();
        bytes.clear();
        bytes = QByteArray::fromRawData(buffTemp, TOTAL_BYTES);
        mutex.unlock();
        //usleep(1000000);
        /*std::cout << "speed: " << dfread.speed << std::endl;
        std::cout << "linear_accel_x: " << dfread.linear_accel_x << std::endl;
        std::cout << "cell_group1_voltage: " << dfread.cell_group1_voltage << std::endl;
        std::cout << "cell_group2_voltage: " << dfread.cell_group2_voltage << std::endl;
        std::cout << "cell_group3_voltage: " << dfread.cell_group3_voltage << std::endl;*/
        //std::cout << "==========================================" << std::endl;
        sleep(1);
    }
}

