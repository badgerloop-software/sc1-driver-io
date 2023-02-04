//
// Created by Mingcan Li on 11/11/21.
//

#ifndef DATAPROCESSOR_DATAGEN_H
#define DATAPROCESSOR_DATAGEN_H

#include <QObject>
#include <QDebug>
#include <ctime>
#include <cstdint>
#include <math.h>
#include <random>

typedef double(*func)(double);

class DataGen{
public:
    DataGen(func speedFunc, func solarFunc, func batteryFunc, float efficiency);

    void getData(QByteArray &data, std::vector<std::string> &names, std::vector<std::string> &types, double timeArg);
private:
    static void addDoubleToArray(QByteArray &dataArr, double data);

    static void addFloatToArray(QByteArray &dataArr, float data);

    template <typename E>
    static void dataToByteArray(QByteArray &dataArr, E data);

    func speedFunc;
    func solarFunc;
    func batteryFunc;
    float efficiency;

    float lastSpeed=0;
    int lastT=0;
    time_t errStartTime=0;
    std::string errors="";

    // Range for random numbers generated for shutdown circuit inputs
    const int SHUTDOWN_RANGE = 600;
    // Upper limit to which the random number is compared for shutdown inputs (randNum < SHUTDOWN_LIMIT -> fault)
    const int SHUTDOWN_LIMIT = 0;
    // Time, in seconds, for which shutdown faults should persist
    const int FAULT_TIME = 3;
};

#endif //DATAGENERATOR_DATAGEN_H
