//
// Created by Mingcan Li on 11/16/21.
//

#include "DataUnpacker.h"

double bytesToDouble(QByteArray data, int start_pos)
{
    double number;
    char* dataPtr = data.data();
    memcpy(&number, &dataPtr[start_pos], sizeof(double));
    return number;
}

float bytesToFloat(QByteArray data, int start_pos)
{
    float number;
    char* dataPtr = data.data();
    memcpy(&number, &dataPtr[start_pos], sizeof(float));
    return number;
}

template <typename E>
E bytesToGeneralData(QByteArray data, int startPos, int endPos, E typeZero)
{
    int byteNum=endPos-startPos;
    auto var = typeZero;

    for(int i = startPos ; i<=endPos ; i++) {
        var=var+data[i]<<byteNum*8;
        byteNum--;
    }

    return var;
}



DataUnpacker::DataUnpacker(QObject *parent) : QObject(parent)
{
    // pi needs an absolute filepath
    FILE* fp = fopen("/Users/mcli/Downloads/solar-car-dashboard-SW-44-tcp-communication/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    if(fp == 0) {
        // testing
        fp = fopen("../sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    }

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);


    for(Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
        std::string name = itr->name.GetString();
        const Value& arr = itr->value.GetArray();
        names.push_back(name);
        byteNums.push_back(arr[0].GetInt());
        types.push_back(arr[1].GetString());
    }

    fclose(fp);

    BackendProcesses* retriever = new BackendProcesses(bytes, names, types);

    retriever->moveToThread(&dataHandlingThread);
    connect(&dataHandlingThread, &QThread::started, retriever, &BackendProcesses::startThread);
    connect(this, &DataUnpacker::getData, retriever, &BackendProcesses::threadProcedure);
    connect(retriever, &BackendProcesses::dataReady, this, &DataUnpacker::unpack);
    connect(&dataHandlingThread, &QThread::finished, retriever, &QObject::deleteLater);
    connect(&dataHandlingThread, &QThread::finished, &dataHandlingThread, &QThread::deleteLater);

    dataHandlingThread.start();
}

DataUnpacker::~DataUnpacker()
{
    dataHandlingThread.quit();
}

void DataUnpacker::unpack()
{
    int currByte = 0;

    for(uint i=0; i < names.size(); i++) {
        if(types[i] == "float") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), bytesToFloat(bytes, currByte));
            }
        } else if(types[i] == "uint8") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), bytesToGeneralData(bytes, currByte, currByte + byteNums[i] - 1, (uint8_t)0));
            }
        } else if(types[i] == "bool") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), bytesToGeneralData(bytes, currByte, currByte + byteNums[i] - 1, false));
            }
        } else if(types[i] == "char") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                // NOTE: char data is displayed as its ASCII decimal value, not the character, so QString is used instead
                this->setProperty(names[i].c_str(), QString::fromStdString(std::string(1, bytesToGeneralData(bytes, currByte, currByte + byteNums[i] - 1, (char)0))));
            }
        } else if(types[i] == "double") {
            // TODO: No double data yet; Implement when there is double data
        }

        currByte += byteNums[i];
    }

    // Signal data update for front end
    emit dataChanged();
    // Signal to get new data
    emit getData();
}
