#include "embedded/controlsWrapper.h"
#include <QDebug>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <embedded/devices/include/ads1219.h>
#include <embedded/devices/src/ads1219.cpp>
#include <embedded/devices/include/tca6416.h>
#include <embedded/devices/src/tca6416.cpp>
#include <embedded/drivers/include/serial.h>
#include <embedded/drivers/src/serial.cpp>
#define T_MESSAGE_MS 1000  // 1 second 
#define HEARTBEAT 2         // go to error state if this # messages that aren't read

Serial serial;
QMutex uartMutex;

#define TOTAL_BYTES 407
controlsWrapper::controlsWrapper(QByteArray &bytes, QMutex &mutex, std::atomic<bool> &restart_enable, int mainIO_heartbeat_offset, int mcu_check_offset, QObject *parent) : QObject(parent), bytes(bytes), mutex(mutex), restart_enable(restart_enable), mainIO_heartbeat_offset(mainIO_heartbeat_offset), mcu_check_offset(mcu_check_offset) {
    //this->bytes = bytes;
    serial = Serial();
    serial.openDevice(0, 115200);
}

// This is the firmware main loop. It's called in a separate thread in DataUnpacker.cpp
// Put your testing code here!
void controlsWrapper::startThread() {
    // initialize tca
    Tca6416 tca = Tca6416(0, 0x20);
    // set enable signals P05, P06, P14, P15, P16 to write (0)
    uint8_t directions[16]= {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1};
    tca.begin(directions);
    // initialize vars for input toggle signals
    uint8_t lblnk_toggle = 0;
    uint8_t rblnk_toggle = 0;
    uint8_t hl_toggle = 0;

    int messages_not_received = 0;
    while(true) {
        // TCA code
        // read input signals
        lblnk_toggle = tca.get_state(0, 0);
        rblnk_toggle = tca.get_state(0, 1);
        hl_toggle = tca.get_state(0, 4);
        // write to enable signals
        tca.set_state(1, 4, lblnk_toggle); // FL_TS_LED_EN
        tca.set_state(1, 5, rblnk_toggle); // FR_TS_LED_EN
        tca.set_state(1, 6, hl_toggle); // F_HL_LED_EN


        // UART code
        std::cout << "===========================================" << std::endl;
        char buffTemp[TOTAL_BYTES];
        // read
        uartMutex.lock();
        // check if we actually read a message 
        int numBytesRead = serial.readBytes(buffTemp, TOTAL_BYTES, T_MESSAGE_MS, 0); 
        if (numBytesRead == 0) {
            std::cout<< "message not received" << std::endl;
            if (++messages_not_received >= HEARTBEAT) {
                std::cout << "heartbeat lost" << std::endl;
                restart_enable = 1;
                mutex.lock();
                // TODO Take a look at backendprocesses.cpp where we set tstamp_hr/mn/sc/ms for setting specific bytes in the byte array
                buffTemp[mainIO_heartbeat_offset] = 0;
                buffTemp[mcu_check_offset] = 1;
                mutex.unlock();
            }
        } else {
            messages_not_received = 0;
            //restart_enable = 0;
        }
        uartMutex.unlock();
        
        // write restart_enable signal
        uartMutex.lock();
        std::cout << "restart_enable: " << restart_enable << std::endl;
        int write = serial.writeBytes(&restart_enable, 1); 
        std::cout << "bytes written: " << write << std::endl;
        uartMutex.unlock();
        
        // copy data in char array to QByteArray
        mutex.lock();
        bytes.clear();
        bytes = QByteArray::fromRawData(buffTemp, TOTAL_BYTES);
        mutex.unlock();
        //usleep(1000000);
        sleep(1);
    }
}

