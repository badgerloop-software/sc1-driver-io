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
#define T_MESSAGE_MS 1000   // 1 second
#define UART_WAIT_US 125000 // .125 seconds
#define BLINK_RATE 62500    // .0625 seconds
#define HEARTBEAT 4         // go to error state if this # messages that aren't read
#define TOTAL_BYTES 441

Serial serial;
QMutex uartMutex;
Tca6416 tca(1, 0x20); // tca objects used to read GPIO pins for lights
INA219 ina(1, 0x44, 0.005, 2.0);
int lblnk_toggle;
int rblnk_toggle;
int hl_toggle;
int brk_toggle;
int hzd_toggle;
int bps_led_toggle;
int blnk;
int blnk_cycle; // controls when the light setting code runs


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
    bps_led_toggle = 0;
    blnk_cycle = 0;

    if(ina.begin() == 1) {
        printf("ina begin threw an error\n");
        sleep(10);
    }
}

controlsWrapper::~controlsWrapper() {
    endControlsWrapper = true; // This will cause the thread's loop to return
}

/* Uses the TCA to read inputs (toggles) and set outputs (enables for lights).
 * Includes code to make the turn signals blink
 */
void set_lights() {
    // read input signals
    lblnk_toggle = tca.get_state(0, 5);
    rblnk_toggle = tca.get_state(0, 4);
    hl_toggle = tca.get_state(0, 2);
    // TODO brake signal was rerouted to the parking brake header: brk_toggle = tca.get_state(0,7);
    brk_toggle = tca.get_state(0, 1); // Parking Brake
    hzd_toggle = tca.get_state(0, 3);

    // TODO Add logic to only toggle the lights/blinkers every N cycles of the main loop (increase UART freq and control blinker freq)
    // TODO Make sure number of flashes is between 60-120 flashes/sec (toggle freq of 120 - 240Hz)
    // TODO Decided on 80 bpm (togles every 375 ms)
    if (true) { //blnk_cycle >= BLINK_RATE / UART_WAIT_US) {
        blnk_cycle = 0;

        // blink code
        if (lblnk_toggle | rblnk_toggle | hzd_toggle | bps_led_toggle) {
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
        printf("bps_led_toggle: %d\n", bps_led_toggle);

        tca.set_state(1, 0, (lblnk_toggle | hzd_toggle) & blnk); // FL_TS_LED_EN
        tca.set_state(1, 5, ((lblnk_toggle | hzd_toggle) & blnk) | (~(lblnk_toggle | hzd_toggle) & brk_toggle)); // BL_TSB_LED_EN
        tca.set_state(1, 2, (rblnk_toggle | hzd_toggle) & blnk); // FR_TS_LED_EN
        tca.set_state(1, 7, ((rblnk_toggle | hzd_toggle) & blnk) | (~(rblnk_toggle | hzd_toggle) & brk_toggle)); // BR_TSB_LED_EN
        tca.set_state(1, 4, hl_toggle); // F_HL_LED_EN
        tca.set_state(1, 6, brk_toggle); //BC_BRK_LED_EN
        tca.set_state(1, 3, bps_led_toggle & blnk); // BC_BPS_LED_EN
    } else {
        blnk_cycle++;
    }
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
void controlsWrapper::mainProcess() {
    // TODO Parking brake was moved to MCC: bool parking_brake = 0;

    // TODO Have Driver IO intiate the connection by sending an ack/handshaek to Main IO to request a packet
    // TODO Write 2 bytes here, and we can use the 2 bytes we normally write (pbrake and restart_en) as the request later
    /* TODO This should be unnecessary
    uartMutex.lock();
    char intial_request[2] = {0, 1}; // TODO Do we want different values?
    int init_write;
    do {
        init_write = serial.writeBytes(initial_request, 2);
        std::cout << "write success: " << write << std::endl;
    } while(!init_write);
    uartMutex.unlock();*/

    printf("bus voltage: %f\n", ina.get_bus_voltage());
    printf("shunt voltage: %f\n", ina.get_shunt_voltage());
    printf("current: %f\n", ina.get_current());
    printf("power: %f\n", ina.get_power());
    printf("---------------------------\n");

    set_lights(); // call method to set the lights using TCA
    // UART code
    char buffTemp[TOTAL_BYTES];
    std::cout << "===========================================" << std::endl;

    // write
    // restart_enable and parking brake
    // This acts as our request for new data
    uartMutex.lock();
    std::cout << "restart_enable: " << restart_enable << std::endl;
    char write_array[2];
    write_array[0] = restart_enable;
    write_array[1] = 0; // TODO Just a stop-gap measure so that we don't have to update the number of bytes expected on Main IO
    // TODO Moved to MCC: write_array[1] = parking_brake;
    // TODO Moved to MCC: parking_brake = tca.get_state(0, 1); // Parking Brake
    int write = serial.writeBytes(write_array, 2);
    std::cout << "write success: " << write << std::endl;
    uartMutex.unlock();



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

    // check bps_fault from MainIO
    printf("bps_fault offset: %d\n", offsets.bps_fault);

    // check things that could trigger bps_fault
    bool bps_fault = buffTemp[offsets.bps_fault];
    float pack_temp = buffTemp[offsets.pack_temp];
    float pack_current = buffTemp[offsets.pack_current];
    float lowest_cell_group_voltage = buffTemp[offsets.lowest_cell_group_voltage];
    float highest_cell_group_voltage = buffTemp[offsets.highest_cell_group_voltage];
    bool imd_status = buffTemp[offsets.imd_status];
    bool charge_enable = buffTemp[offsets.charge_enable];
    bool discharge_enable = buffTemp[offsets.discharge_enable];
    bool voltage_failsafe = buffTemp[offsets.voltage_failsafe];
    bool external_eStop = buffTemp[offsets.external_eStop];

    if (/*TODO pack_temp > 36
        || pack_current < -24.4 || pack_current > 48.8
        || lowest_cell_group_voltage < 2.5 || highest_cell_group_voltage > 3.65
        || imd_status ||*/ charge_enable || discharge_enable // TODO || voltage_failsafe || external_eStop
        ) {
        bps_led_toggle = 1;
        buffTemp[offsets.bps_fault] = 1; // set bps_fault in driverIO data format
    } else {
        bps_led_toggle = 0;
        buffTemp[offsets.bps_fault] = 0; // set bps_fault in driverIO data format
    }

    // TODO Potentially wait to read a request from Main IO acknowledging that it wants data (can probably take it for granted right now)
    //int numBytesRead = serial.readBytes(buffTemp, TOTAL_BYTES, T_MESSAGE_MS, 0);


    // write
    // restart_enable and parking brake
    // TODO This acts as our request for new data
    /* TODO
    uartMutex.lock();
    std::cout << "restart_enable: " << restart_enable << std::endl;
    char write_array[2];
    write_array[0] = restart_enable;
    write_array[1] = parking_brake;
    //parking_brake = !parking_brake; // TODO: remove this line. It's used for testing purposes.
    parking_brake = tca.get_state(0, 1); // Parking Brake
    int write = serial.writeBytes(write_array, 2);
    std::cout << "write success: " << write << std::endl;
    uartMutex.unlock();*/

    // set lights in buffTemp to send to software
    buffTemp[offsets.headlights] = hl_toggle;
    buffTemp[offsets.headlights_led_en] = hl_toggle;
    buffTemp[offsets.right_turn] = rblnk_toggle;
    buffTemp[offsets.fr_turn_led_en] = (blnk & rblnk_toggle);
    buffTemp[offsets.br_turn_led_en] = (blnk & rblnk_toggle);
    buffTemp[offsets.left_blinker] = lblnk_toggle;
    buffTemp[offsets.fl_turn_led_en] = (blnk & lblnk_toggle);
    buffTemp[offsets.bl_turn_led_en] = (blnk & lblnk_toggle);
    buffTemp[offsets.bc_bps_led_en] = (blnk & bps_led_toggle);
    buffTemp[offsets.bc_brake_led_en] = brk_toggle;

    // copy data in char array to QByteArray
    mutex.lock();
    bytes.clear();
    // TODO Have Driver IO intiate the connection by sending an ack/handshaek to Main IO to request a packet

    bytes = QByteArray::fromRawData(buffTemp, TOTAL_BYTES);
    mutex.unlock();

    usleep(UART_WAIT_US);
    //sleep(1);
    emit endMainProcess();
}
