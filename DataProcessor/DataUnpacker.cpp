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
        var = var + (((uint8_t) data[i]) << (byteNum * 8));
        byteNum--;
    }

    return var;
}



DataUnpacker::DataUnpacker(QObject *parent) : QObject(parent)
{
    FILE* fp = fopen("../sc1-driver-io/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    if(fp == 0) {
        fp = fopen("../sc1-driver-io/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    }

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);

    int arrayOffset = 0;
    timestampOffsets tstampOff;
    int dataCount = 0;
    cell_group_voltages_begin = -1;
    cell_group_voltages_end = -1;

    for(Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
        std::string name = itr->name.GetString();
        const Value& arr = itr->value.GetArray();

        names.push_back(name);
        byteNums.push_back(arr[0].GetInt());
        types.push_back(arr[1].GetString());

        if(name == "tstamp_hr") {
            tstampOff.hr = arrayOffset;
        } else if(name == "tstamp_mn") {
            tstampOff.mn = arrayOffset;
        } else if(name == "tstamp_sc") {
            tstampOff.sc = arrayOffset;
        } else if(name == "tstamp_ms") {
            tstampOff.ms = arrayOffset;
        } else if(name.substr(0, 10) == "cell_group") {
            if(cell_group_voltages_begin == -1) {
                cell_group_voltages_begin = dataCount;
            } else {
                cell_group_voltages_end = dataCount;
            }
            cell_group_voltages.push_back(0);
        }
        qDebug() << cell_group_voltages_begin;
        arrayOffset += arr[0].GetInt();
        dataCount++;
    }

    fclose(fp);

    BackendProcesses* retriever = new BackendProcesses(bytes, names, types, tstampOff,mutex);

    retriever->moveToThread(&dataHandlingThread);
    connect(&dataHandlingThread, &QThread::started, retriever, &BackendProcesses::startThread);
    connect(this, &DataUnpacker::getData, retriever, &BackendProcesses::threadProcedure);
    connect(retriever, &BackendProcesses::dataReady, this, &DataUnpacker::unpack);
    connect(retriever, &BackendProcesses::eng_dash_connected, this, &DataUnpacker::eng_dash_connected);
    connect(retriever, &BackendProcesses::eng_dash_disconnected, this, &DataUnpacker::eng_dash_disconnected);
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

    mutex.lock();
    for(uint i=0; i < names.size(); i++) {
        if(types[i] == "float") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), bytesToFloat(bytes, currByte));
            } else if((i >= cell_group_voltages_begin) && (i <= cell_group_voltages_end)) {
                cell_group_voltages[i - cell_group_voltages_begin] = bytesToFloat(bytes, currByte);
            }
        } else if(types[i] == "uint8") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), bytesToGeneralData(bytes, currByte, currByte + byteNums[i] - 1, (uint8_t)0));
            }
        } else if(types[i] == "uint16") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                this->setProperty(names[i].c_str(), bytesToGeneralData(bytes, currByte, currByte + byteNums[i] - 1, (uint16_t)0));
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

    mutex.unlock();
    this->restart_enable = !battery_eStop || !driver_eStop || !external_eStop || !imd_status || !door || crash || !mcu_check || restart_enable;

    // Signal data update for front end
    emit dataChanged();
    // Signal to get new data
    emit getData();
}

void DataUnpacker::eng_dash_connected() {
    eng_dash_commfail = 0;
}

void DataUnpacker::eng_dash_disconnected() {
    eng_dash_commfail = 1;
}
