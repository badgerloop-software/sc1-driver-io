//
// Created by Mingcan Li on 11/11/21.
//

#ifndef DATAPROCESSOR_DATAGEN_H
#define DATAPROCESSOR_DATAGEN_H

#include <QObject>
#include <ctime>
#include <cstdint>
#include <math.h>
#include <random>

typedef double(*func)(double);

class DataGen{
public:
    DataGen(func speedFunc, func solarFunc, func batteryFunc, float efficiency);

    void getData(QByteArray &data, std::vector<std::string> &names, std::vector<std::string> &types, double time);
private:
    static void addDoubleToArray(QByteArray &dataArr, double data);

    static void addFloatToArray(QByteArray &dataArr, float data);

    template <typename E>
    static void dataToByteArray(QByteArray &dataArr, E data);

    func speedFunc;
    func solarFunc;
    func batteryFunc;
    float efficiency;
};

#endif //DATAGENERATOR_DATAGEN_H
