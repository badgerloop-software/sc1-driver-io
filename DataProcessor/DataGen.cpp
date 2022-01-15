//
// Created by Mingcan Li on 11/11/21.
//

#include "DataGen.h"

int lastSpeed=0;
int lastT=0;

/**
 * Generates an array of test data
 * @param data The vector array to store the data, put an empty vector.
 * @param time time
 */
void DataGen::getData(QByteArray &data, double time) {
    //speed
    dataToByteArray(data,(uint8_t)speedFunc(time));
    //charge
    dataToByteArray(data,(uint8_t)batteryFunc(time));
    //solar power
    addFloatToArray(data,(float)solarFunc(time));
    //battery voltage
    addFloatToArray(data,(float)sqrt(abs(solarFunc(time)-0.5*1000*(speedFunc(time)*speedFunc(time)-lastSpeed*lastSpeed)/efficiency)));
    //battery current
    addFloatToArray(data,(float)sqrt(abs(solarFunc(time)-0.5*1000*(speedFunc(time)*speedFunc(time)-lastSpeed*lastSpeed)/efficiency)));
    //net power
    addFloatToArray(data,(float)solarFunc(time)-0.5*1000*(speedFunc(time)*speedFunc(time)-lastSpeed*lastSpeed)/efficiency);
    //motor power
    addFloatToArray(data,(float)(0.5*1000*(speedFunc(time)*speedFunc(time)-lastSpeed*lastSpeed)/efficiency));
    //state
    dataToByteArray(data,'D');
    //battery temp
    addFloatToArray(data,(float)rand()/((RAND_MAX+1u)/200));
    //motor temp
    addFloatToArray(data,(float)rand()/((RAND_MAX+1u)/200));
    //motor controller temp
    addFloatToArray(data,(float)rand()/((RAND_MAX+1u)/200));
    //bps fault
    dataToByteArray(data,rand()>rand());
    //estop
    dataToByteArray(data,rand()>rand());
    //cruise control
    dataToByteArray(data,rand()>rand());
    //left turn
    dataToByteArray(data,rand()>rand());
    //right turn
    dataToByteArray(data,rand()>rand());
    //FL TP
    dataToByteArray(data,(uint8_t)fmod(rand(),200));
    //FR TP
    dataToByteArray(data,(uint8_t)fmod(rand(),200));
    //RL TP
    dataToByteArray(data,(uint8_t)fmod(rand(),200));
    //RR TP
    dataToByteArray(data,(uint8_t)fmod(rand(),200));
    //battery group 1
    addFloatToArray(data,(float)batteryFunc(time));
    //battery group 2
    addFloatToArray(data,(float)batteryFunc(time));
    //battery group 3
    addFloatToArray(data,(float)batteryFunc(time));
    //battery group 4
    addFloatToArray(data,(float)batteryFunc(time));
}

DataGen::DataGen(func speedFunc, func solarFunc, func batteryFunc, float efficiency) {
    this->speedFunc=speedFunc;
    this->solarFunc=solarFunc;
    this->efficiency=efficiency;
    this->batteryFunc=batteryFunc;
    srand(static_cast<int>(time(0)));
}

/**
 * Since double cannot use bitwise operand, this method adds a double to the array
 * @param dataArr the data put into this array
 * @param data double data
 */
void DataGen::addDoubleToArray(QByteArray &dataArr, double data) {
    const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&data);
    for (size_t i = 0; i < sizeof(double); ++i)
        dataArr.push_back(ptr[i]);
}

/**
 * Since float cannot use bitwise operand, this method adds a float to the array
 * @param dataArr the data put into this array
 * @param data float data
 */
void DataGen::addFloatToArray(QByteArray &dataArr, float data) {
    const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&data);
    for (size_t i = 0; i < sizeof(float); ++i)
        dataArr.push_back(ptr[i]);
}

/**
 * A generic function to put data into array
 * @tparam E any type of data that can use binary operand
 * @param dataArr data put into this array
 * @param data
 */
template<typename E>
void DataGen::dataToByteArray(QByteArray &dataArr, E data) {
    for (int i = sizeof(data)-1; i >= 0 ; i--) {
        dataArr.push_back(data >> (8 * i) & 0xFF);
    }
}






