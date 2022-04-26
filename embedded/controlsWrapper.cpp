#include "embedded/controlsWrapper.h"
#include <QDebug>
#include <ctime>
#include <unistd.h>
#include <embedded/devices/include/ads1219.h>
#include <embedded/devices/src/ads1219.cpp>

controlsWrapper::controlsWrapper() {

}

// This is the firmware main loop. It's called in a separate thread in DataUnpacker.cpp
// Put your testing code here!
void controlsWrapper::startThread() {
    // test ads1219
    Ads1219 testADS = new Ads1219(1, 0x40);
    testADS.begin();
    // loop goes here
    while(true) {
        qDebug() << "test\n";
        sleep(5);
        std::cout << "Channel 0: " << testADS.getVoltage(0);
        std::cout << "Channel 1: " << testADS.getVoltage(1);
        std::cout << "Channel 2: " << testADS.getVoltage(2);
        std::cout << "Channel 3: " << testADS.getVoltage(3);
    }
}