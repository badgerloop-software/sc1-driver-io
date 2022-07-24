#include "embedded/controlsWrapper.h"
#include <QDebug>
#include <ctime>
#include <unistd.h>
#include <embedded/devices/include/ads1219.h>
#include <embedded/devices/src/ads1219.cpp>
#include <embedded/devices/include/ina3221.h>
#include <embedded/devices/src/ina3221.cpp>
#include <embedded/drivers/include/i2c.h>
#include <embedded/drivers/src/i2c.cpp>
#include <embedded/drivers/include/i2c-dev.h>
#include <embedded/drivers/include/gpio.h>
#include <embedded/drivers/src/gpio.cpp>

controlsWrapper::controlsWrapper() {

}

// This is the firmware main loop. It's called in a separate thread in DataUnpacker.cpp
// Put your testing code here!
void controlsWrapper::startThread() {
    // test ads1219
    // Ads1219 testADS = Ads1219(1, 0x40);
    // testADS.begin();

    // test ina3221
    // Ina3221 test = Ina3221(0, 0x41, 0.005, 0.005, 0.005);
    // test.begin();
    // std::cout << "Ina3221" << std::endl;
    // loop goes here

    // // test i2c
    // I2c testI2c = I2c(0, 0x41, 02);
    // testI2c.open_i2c();
    // uint8_t reg = 1;
    // std::cout << "write byte test: " << testI2c.write_byte(reg);
    // std::cout << "read data test: ";
    // std::cout << "read from reg test: " << testI2c.read_from_reg(reg);  
    // std::cout << "read bytes from reg test: ";
    
    // test GPIO
    // 1 is input, 0 is output

    Gpio testOutput = Gpio(16, 0);
    testOutput.begin();

    while(true) {
        // qDebug() << "test\n";
        // std::cout << "Channel 0: " << testADS.getVoltage(0);
        // std::cout << "Channel 1: " << testADS.getVoltage(1);
        // std::cout << "Channel 2: " << testADS.getVoltage(2);
        // std::cout << "Channel 3: " of<< testADS.getVoltage(3);
        // std::cout << "channel 1 voltage: " << test.readVoltage(0x1) << std::endl;
        // std::cout << "channel 2 voltage: " << test.readVoltage(0x2) << std::endl;
        // std::cout << "channel 3 voltage: " << test.readVoltage(0x3) << std::endl;
        // std::cout << "channel 3 current: " << test.readCurrent(0x3) << std::endl;
        // std::cout << std::endl;
        std::cout << "Set pin 16 to 1\n";
        testOutput.setValue(1);
        usleep(5000000);
        std::cout << "Set pin 16 to 0\n";
        testOutput.setValue(0);
        usleep(5000000);
    }
}