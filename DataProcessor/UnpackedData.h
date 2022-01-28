#ifndef UNPACKEDDATA_H
#define UNPACKEDDATA_H
#include <cstdio>
#include <cstdint>

struct unpackedData{
    //1 byte stuffs
    uint8_t speed, charge, flTp, frTp, rlTp, rrTp;
    char state;
    bool bpsFault, eStop, cruiseControl, leftTurn, rightTurn;
    //4 byte stuffs
    float solarPower, motorPower, netPower, batteryVoltage, batteryCurrent, batteryTemp, motorTemp,
          motorControllerTemp, bat1, bat2, bat3, bat4;
};

#endif // UNPACKEDDATA_H
