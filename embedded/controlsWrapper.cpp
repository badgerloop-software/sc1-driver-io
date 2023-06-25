#include "embedded/controlsWrapper.h"
#include <QDebug>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include <embedded/devices/include/ads1219.h>
#include <embedded/devices/src/ads1219.cpp>
#include <embedded/devices/include/ina219.h>
#include <embedded/devices/src/ina219.cpp>
#include <embedded/devices/include/tca6416.h>
#include <embedded/devices/src/tca6416.cpp>
#include <embedded/drivers/include/serial.h>
#include <embedded/drivers/src/serial.cpp>
#define T_MESSAGE_MS 1000  // 1 second 
#define HEARTBEAT 2         // go to error state if this # messages that aren't read

Serial serial;
QMutex uartMutex;
Tca6416 tca(1, 0x20); // tca objects used to read GPIO pins for lights
int lblnk_toggle;
int rblnk_toggle;
int hl_toggle;
int brk_toggle;
int hzd_toggle;
int blnk; 


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

    
    // set enable signals to write (0)
    uint8_t directions[16]= {1, 1, 1, 1, 1, 1, 1, 1, 
                                0, 1, 0, 0, 0, 0, 0, 0};
    tca.begin(directions);
    // initialize lights to 0
    tca.set_state(1, 7, 0); // BR_TSB_LED_EN back right turn signal
    tca.set_state(1, 6, 0); // BC_BRK_LED_EN
    tca.set_state(1, 5, 0); // BL_TSB_LED_EN back left turn signal
    tca.set_state(1, 4, 0); // F_HL_LED_EN front headlight
    tca.set_state(1, 3, 0); // BC_BPS_LED_EN
    tca.set_state(1, 2, 0); // FR_TS_LED_EN front right turn signal
    tca.set_state(1, 0, 0); // FL_TS_LED_EN front left turn signal
    

    // initialize values of global ints
    blnk = 0;
    lblnk_toggle = 0;
    rblnk_toggle = 0;
    hl_toggle = 0;
    brk_toggle = 0;
    hzd_toggle = 0;
}

/* Uses the TCA to read inputs (toggles) and set outputs (enables for lights).
 * Includes code to make the turn signals blink 
 */
void set_lights() {
    // read input signals
    lblnk_toggle = tca.get_state(0, 5);
    rblnk_toggle = tca.get_state(0, 4);
    hl_toggle = tca.get_state(0, 2);
    brk_toggle = tca.get_state(0,7);
    hzd_toggle = tca.get_state(0,3);

    // blink code 
    if (lblnk_toggle | rblnk_toggle | hzd_toggle) {
        if (blnk == 0) {
            blnk = 1;
        } else {
            blnk = 0;
        }
    } else {
        blnk = 0;
    }

    // set lights
    printf("blnk: %d\n", blnk);
    printf("lblnk_toggle: %d\n", lblnk_toggle);
    printf("rblnk_toggle: %d\n", rblnk_toggle);
    printf("hl_toggle: %d\n", hl_toggle);
    printf("brk_toggle: %d\n", brk_toggle);
    printf("hzd_toggle: %d\n", hzd_toggle);
    
    tca.set_state(1, 0, (lblnk_toggle | hzd_toggle) & blnk); // FL_TS_LED_EN
    tca.set_state(1, 5, ((lblnk_toggle | hzd_toggle) & blnk) | (~(lblnk_toggle | hzd_toggle) & brk_toggle)); // BL_TSB_LED_EN
    tca.set_state(1, 2, (rblnk_toggle | hzd_toggle) & blnk); // FR_TS_LED_EN
    tca.set_state(1, 7, ((rblnk_toggle | hzd_toggle) & blnk) | (~(rblnk_toggle | hzd_toggle) & brk_toggle)); // BR_TSB_LED_EN
    tca.set_state(1, 4, hl_toggle); // F_HL_LED_EN
    tca.set_state(1, 6, brk_toggle); //BC_BRK_LED_EN
}


/* Debug method used to printout all pins of the TCA that are 1.
 * Useful to see if flipping a hardware switch will be read by the TCA.
 */
 /*
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
*/
// This is the firmware main loop. It's called in a separate thread in DataUnpacker.cpp
// Put your testing code here!
void controlsWrapper::startThread() {
    INA219 ina = INA219(1, 0x44, 0.005, 2.0);
    if(ina.begin() == 1) {
        printf("ina begin threw an error\n");
        sleep(10);
    }
    int messages_not_received = 0;
    bool parking_brake = 0;
    while(true) {

        printf("bus voltage: %f\n", ina.get_bus_voltage());
        printf("shunt voltage: %f\n", ina.get_shunt_voltage());
        printf("current: %f\n", ina.get_current());
        printf("power: %f\n", ina.get_power());
        printf("---------------------------\n");

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
        
        /*
        // check bps_fault from MainIO
        bool bps_fault = buffTemp[offsets.bps_fault];
        printf("bps_fault offset: %d\n", offsets.bps_fault);
        */

        // write 
        // restart_enable and parking brake
        uartMutex.lock();
        std::cout << "restart_enable: " << restart_enable << std::endl;
        char write_array[2]; 
        write_array[0] = restart_enable; 
        write_array[1] = parking_brake; 
        //parking_brake = !parking_brake; // TODO: remove this line. It's used for testing purposes. 
        parking_brake = tca.get_state(0, 1); // Parking Brake
        int write = serial.writeBytes(write_array, 2); 
        std::cout << "write success: " << write << std::endl;
        uartMutex.unlock();
 
        // set lights in buffTemp to send to software      
        buffTemp[offsets.headlights] = hl_toggle;
        buffTemp[offsets.headlights_led_en] = hl_toggle;
        buffTemp[offsets.right_turn] = rblnk_toggle;
        buffTemp[offsets.fr_turn_led_en] = (blnk & rblnk_toggle);
        buffTemp[offsets.left_blinker] = lblnk_toggle;
        buffTemp[offsets.fl_turn_led_en] = (blnk & lblnk_toggle);

        // copy data in char array to QByteArray
        mutex.lock();
        bytes.clear();
        bytes = QByteArray::fromRawData(buffTemp, TOTAL_BYTES);
        mutex.unlock();

        //usleep(1000000);
        sleep(1);
        
    }
}

