//
// Created by Mingcan Li on 11/11/21.
//
//This file provides an example use of the data generator program.

#include <iostream>
#include "DataGen.h"
#include <vector>
#include <math.h>
#include "DataUnpacker.h"

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

int main() {

}


