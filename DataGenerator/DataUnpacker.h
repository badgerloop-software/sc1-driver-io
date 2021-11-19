//
// Created by Mingcan Li on 11/16/21.
//

#ifndef DATAGENERATOR_DATAUNPACKER_H
#define DATAGENERATOR_DATAUNPACKER_H

#include <vector>

using namespace std;
typedef unsigned char byte;

class DataUnpacker {
public:
    int speed, charge, flTp, frTp, rlTp, rrTp;
    double power, solarP, netP, motorP, batteryT, motorT, motorControllerT;
    char state;
    bool bpsFault, eStop, cruise, lt, rt;
    DataUnpacker(vector<byte> rawData);
    void unpack(vector<byte> rawData);
};


#endif //DATAGENERATOR_DATAUNPACKER_H
