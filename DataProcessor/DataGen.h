//
// Created by Mingcan Li on 11/11/21.
//

#ifndef DATAGENERATOR_DATAGEN_H
#define DATAGENERATOR_DATAGEN_H

#include <vector>
#include <random>
#include <QObject>
#include <ctime>
typedef double(*func)(double);
typedef unsigned char byte;

//using namespace std;

class DataGen{
public:

    DataGen(func speedFunc, func solarFunc, func batteryFunc, float efficiency);

    void getData(std::vector<byte> &data, double time);

    static void addDoubleToArray(std::vector<byte> &dataVec, double data);

    template <typename E>
    static void dataToByteArray(std::vector<byte> &dataVec, E data);
private:
    func speedFunc;
    func solarFunc;
    func batteryFunc;
    float efficiency;
};

#endif //DATAGENERATOR_DATAGEN_H
