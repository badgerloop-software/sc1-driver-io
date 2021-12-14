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
void DataGen::getData(std::vector<byte> &data, double time) {
    //speed
    dataToByteArray(data,(int)speedFunc(time));
    //power
    addDoubleToArray(data,0.5*1000*(speedFunc(time)*speedFunc(time)-lastSpeed*lastSpeed));
    //Charge
    dataToByteArray(data,(int)batteryFunc(time));
    //Solar power
    addDoubleToArray(data,solarFunc(time));
    //net power
    addDoubleToArray(data,solarFunc(time)-0.5*1000*(speedFunc(time)*speedFunc(time)-lastSpeed*lastSpeed)/efficiency);
    //motor power
    addDoubleToArray(data,0.5*1000*(speedFunc(time)*speedFunc(time)-lastSpeed*lastSpeed)/efficiency);
    //state
    dataToByteArray(data,'D');
    //Battery Temp
    addDoubleToArray(data,arc4random_uniform(200));
    //Motor Temp
    addDoubleToArray(data,arc4random_uniform(200));
    //Motor Controller Temp
    addDoubleToArray(data,arc4random_uniform(200));
    //bps Fault
    dataToByteArray(data,arc4random()>arc4random());
    //estop
    dataToByteArray(data,arc4random()>arc4random());
    //cruise control
    dataToByteArray(data,arc4random()>arc4random());
    //left turn
    dataToByteArray(data,arc4random()>arc4random());
    //right turn
    dataToByteArray(data,arc4random()>arc4random());
    //FL TP
    dataToByteArray(data,(int)fmod(arc4random(),200));
    //FR TP
    dataToByteArray(data,(int)fmod(arc4random(),200));
    //RL TP
    dataToByteArray(data,(int)fmod(arc4random(),200));
    //RR TP
    dataToByteArray(data,(int)fmod(arc4random(),200));
}

DataGen::DataGen(func speedFunc, func solarFunc, func batteryFunc, float efficiency) {
    this->speedFunc=speedFunc;
    this->solarFunc=solarFunc;
    this->efficiency=efficiency;
    this->batteryFunc=batteryFunc;
    srand(static_cast<int>(time(0)));
}

/**
 * Since double cannot use bitwise operand, this method add double to the array
 * @param dataVec the data put into this array
 * @param data double data
 */
void DataGen::addDoubleToArray(std::vector<byte> &dataVec, double data) {
    const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&data);
    for (size_t i = 0; i < sizeof(double); ++i)
        dataVec.push_back(ptr[i]);
}

/**
 * A generic function to put data into array
 * @tparam E any type of data that can use binary operand
 * @param dataVec data put into this array
 * @param data
 */
template<typename E>
void DataGen::dataToByteArray(std::vector<byte> &dataVec, E data) {
    for (int i = sizeof(data)-1; i >= 0 ; i--) {
        dataVec.push_back(data >> (8 * i) & 0xFF);
    }
}






