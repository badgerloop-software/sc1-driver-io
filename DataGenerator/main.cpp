//
// Created by Mingcan Li on 11/11/21.
//
//This file provides an example use of the data generator program.
#include <iostream>
#include "DataGen.h"
#include <vector>
#include <math.h>

using namespace std;

double speedFunc(double t){
    return t*t;
}

double solarFunc(double t){
    return t*t*t;
}

double batteryFunc(double t){
    return pow(2.71828,-t);
}

void bytesToDouble(vector<unsigned char> data, int start_pos) {
    double number;
    memcpy(&number, &data.at(start_pos), sizeof(double));
    std::cout << number << std::endl;
}

int main() {
    vector<unsigned char> data;
    DataGen dataSource(&speedFunc,&solarFunc,&batteryFunc,100);
    dataSource.getData(data, 5);
    bytesToDouble(data,4);
}


