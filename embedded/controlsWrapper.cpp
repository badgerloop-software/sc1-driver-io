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
Tca6416 tca(0, 0x20); // tca objects used to read GPIO pins for lights
int lblnk_toggle;
int rblnk_toggle;
int hl_toggle;
int lblnk; 
int rblnk; 


#define TOTAL_BYTES 431
/*
 * bytes the byte array that software uses
 * mutex the mutex for that byte array
 * restart_enable the command DriverIO sends to MainIO
 * offsets the offsets for values in the byte array that firmware sets for software (lights, mainIO_heartbeat)
 */
controlsWrapper::controlsWrapper(QByteArray &bytes, QMutex &mutex, std::atomic<bool> &restart_enable, controlsOffsets offsets, QObject *parent) : QObject(parent), bytes(bytes), mutex(mutex), restart_enable(restart_enable), offsets(offsets) {
    // initialize UART
    serial = Serial();
    serial.openDevice(0, 115200);

    // initialize tca
    tca = Tca6416(0, 0x20);
    // set enable signals P00, P04, P10, P16, P17 to write (0)
    uint8_t directions[16]= {0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0};
    tca.begin(directions);
    // initialize lights to 0
    tca.set_state(1, 0, 0); // FL_TS_LED_EN
    tca.set_state(1, 7, 0); // FR_TS_LED_EN
    tca.set_state(1, 6, 0); // HL_LED_EN

    // initialize values of global ints
    lblnk = 0;
    rblnk = 0;
    lblnk_toggle = 0;
    rblnk_toggle = 0;
    hl_toggle = 0;
}

/* Uses the TCA to read inputs (toggles) and set outputs (enables for lights).
 * Includes code to make the turn signals blink 
 */
void set_lights() {
    // read input signals
    lblnk_toggle = tca.get_state(0, 7);
    rblnk_toggle = tca.get_state(0, 6);
    hl_toggle = tca.get_state(0, 5);

    // blink code 
    if (lblnk_toggle == 1) {
        if (lblnk == 0) {
            lblnk = 1;
        } else {
            lblnk = 0;
        }
    } else {
        lblnk = 0;
    }
    if (rblnk_toggle == 1) {
        if (rblnk == 0) {
            rblnk = 1;
        } else {
            rblnk = 0;
        }
    } else {
        rblnk = 0;
    }

    // set lights 
    tca.set_state(1, 0, lblnk); // FL_TS_LED_EN
    tca.set_state(1, 7, rblnk); // FR_TS_LED_EN
    tca.set_state(1, 6, hl_toggle); // F_HL_LED_EN
}

/* Debug method used to printout all pins of the TCA that are 1.
 * Useful to see if flipping a hardware switch will be read by the TCA.
 */
void printout_tca() {
    // print out all tca pins that are 1 
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 8; j++) {
            int k = tca.get_state(i, j);
            if (k == 1) {
                std::cout << "||||||||||||||||||||||||||||| " << i << ", " << j << ": " << k << std::endl;
            }
        }
    }
}

// This is the firmware main loop. It's called in a separate thread in DataUnpacker.cpp
// Put your testing code here!
void controlsWrapper::startThread() {
    int messages_not_received = 0;
    bool parking_brake = 0;
    while(true) {
        set_lights(); // call method to set the lights using TCA
        char buffTemp[TOTAL_BYTES];
        // UART code
        std::cout << "===========================================" << std::endl;
        
        // read
        uartMutex.lock();
        // check if we actually read a message 
        int numBytesRead = serial.readBytes(buffTemp, TOTAL_BYTES, T_MESSAGE_MS, 0); 
        if (numBytesRead == 0) {
            std::cout << "message not received" << std::endl;
            if (++messages_not_received >= HEARTBEAT) {
                std::cout << "heartbeat lost" << std::endl;
                restart_enable = 1;
                // overwrite mainIO_heartbeat and mcu_check
                buffTemp[offsets.mainIO_heartbeat] = 0;
                buffTemp[offsets.mcu_check]= 1;
            }
        } else {
            messages_not_received = 0;
        }
        uartMutex.unlock();
        
        // write restart_enable signal
        uartMutex.lock();
        std::cout << "restart_enable: " << restart_enable << std::endl;
        char write_array; 
        write_array[0] = restart_enable; 
        write_array[1] = parking_brake; 
        parking_brake = !parking_brake; // TODO: remove this line. It's used for testing purposes. 
        int write = serial.writeBytes(write_array, 2); 
        std::cout << "bytes written: " << write << std::endl;
        uartMutex.unlock();
 
        // set lights in buffTemp to send to software      
        buffTemp[offsets.headlights] = hl_toggle;
        buffTemp[offsets.headlights_led_en] = hl_toggle;
        buffTemp[offsets.right_turn] = rblnk_toggle;
        buffTemp[offsets.fr_turn_led_en] = rblnk;
        buffTemp[offsets.left_blinker] = lblnk_toggle;
        buffTemp[offsets.fl_turn_led_en] = lblnk;

        // copy data in char array to QByteArray
        mutex.lock();
        bytes.clear();
        bytes = QByteArray::fromRawData(buffTemp, TOTAL_BYTES);
        mutex.unlock();

        //usleep(1000000);
        sleep(1);
    }
}

