//
// Created by Mingcan Li on 11/11/21.
//

#ifndef DATAPROCESSOR_DATAGEN_H
#define DATAPROCESSOR_DATAGEN_H

// TODO #include <vector>
#include <random>
#include <QObject>
#include <ctime>
#include <cstdio>
#include <cstdint>
#include <math.h>

typedef double(*func)(double);
typedef unsigned char byte;

//using namespace std;

class DataGen{
public:

    DataGen(func speedFunc, func solarFunc, func batteryFunc, float efficiency);

    void getData(QByteArray &data, double time);

    static void addDoubleToArray(QByteArray &dataArr, double data);

    static void addFloatToArray(QByteArray &dataArr, float data);

    template <typename E>
    static void dataToByteArray(QByteArray &dataArr, E data);

private:
    func speedFunc;
    func solarFunc;
    func batteryFunc;
    float efficiency;
};

#endif //DATAGENERATOR_DATAGEN_H
