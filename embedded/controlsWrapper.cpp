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

Serial serial;
QMutex uartMutex;

#define TOTALBYTES 297
controlsWrapper::controlsWrapper(QByteArray &bytes, QMutex &mutex, QObject *parent) : QObject(parent), bytes(bytes), mutex(mutex)  {
    this->bytes = bytes;
    serial = Serial();
    serial.openDevice(0, 115200);
}


// This is the firmware main loop. It's called in a separate thread in DataUnpacker.cpp
// Put your testing code here!
void controlsWrapper::startThread() {
    // loop goes here
    while(true) {
        char buffTemp[TOTALBYTES];
        uartMutex.lock();
        serial.readBytes(buffTemp, TOTALBYTES, 1000, 0);
        uartMutex.unlock();
        mutex.lock();
        bytes.clear();
        //bytes.remove(0, TOTALBYTES);
        //bytes.insert(0, (char*)&dfread);
        bytes = QByteArray::fromRawData(buffTemp, TOTALBYTES);
        //bytes.replace(0, TOTALBYTES, (char*)&dfread, (int)sizeof(char));
        //printf("char array size: %i\n", sizeof(buffTemp));
        //printf("dfread: %s\n", dfread);
        //qDebug() << "controls bytes: " << bytes.toHex();
        mutex.unlock();
        //usleep(1000000);
        /*std::cout << "speed: " << dfread.speed << std::endl;
        std::cout << "linear_accel_x: " << dfread.linear_accel_x << std::endl;
        std::cout << "cell_group1_voltage: " << dfread.cell_group1_voltage << std::endl;
        std::cout << "cell_group2_voltage: " << dfread.cell_group2_voltage << std::endl;
        std::cout << "cell_group3_voltage: " << dfread.cell_group3_voltage << std::endl;*/
        //std::cout << "==========================================" << std::endl;
    }

    /*
        std::string checkMessage = "";
        // write a random number of bytes (1-9) to the BBB
        unsigned int numWriteBytes = rand() % 9 + 1;
        char nwb = char(numWriteBytes + 48); // convert number of bytes to char
        serial.writeString(&nwb); // write number of bytes
        for(int i = 0; i < numWriteBytes; i++) { // write message using for loop
            serial.writeString(&message[i]);
            checkMessage = checkMessage + message[i];
        }
        std::cout << "write: " << nwb << checkMessage << std::endl;
        usleep(1000000);

        // read the number of bytes of incoming data
        char readBytesIn[1];
        serial.readString(readBytesIn, 1);
        unsigned int numReadBytes = (int)readBytesIn[0] - 48;
        std::cout << "nrb: " << numReadBytes << " char: " << readBytesIn << std::endl;

        // read that number of bytes to get the data
        char readResult[numReadBytes];
        serial.readString(readResult, numReadBytes);
        std::cout << "read: " << readResult << std::endl;
        usleep(1000000);
        serial.flushReceiver();
        */
}

// method to send enableRestart signal to MainIO
// only runs when all faults are cleared and the screen is tapped. `
void controlsWrapper::sendEnableRestart() {
    qDebug() << "controls: restart enable signal sent\n";
    //bool enableRestart = 1;
    //serial.writeBytes(&enableRestart, 1); 
    //printf("restart enable signal sent\n");
}
