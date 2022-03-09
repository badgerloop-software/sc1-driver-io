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
        if(sizeof(var) == 2) {
            qDebug() << "unpack (" << i << "): " << ((uint8_t)(data[i])<<(byteNum*8));
            qDebug() << "unpack (" << i << "): " << 0+data[i];
        }
        var = var + (((uint8_t) data[i]) << (byteNum * 8));
        byteNum--;
    }

    if(sizeof(var) == 2) {
        qDebug() << "unpacked: " << var;
    }

    return var;
}



DataUnpacker::DataUnpacker(QObject *parent) : QObject(parent)
{
    FILE* fp = fopen("../sc1-driver-io/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    if(fp == 0) {
        fp = fopen("../solar-car-dashboard/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    }

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);

    int arrayOffset = 0;
    timestampOffsets tstampOff;

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
        }
        arrayOffset += arr[0].GetInt();
    }

    fclose(fp);

    BackendProcesses* retriever = new BackendProcesses(bytes, names, types, tstampOff);

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
        } else if(types[i] == "uint16") {
            // Make sure the property exists
            if(this->property(names[i].c_str()).isValid()) {
                //uint64_t curr_msec = llround(std::chrono::duration<uint64_t, std::milli>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())).count());
                //uint16_t msec_time = curr_msec % 1000;
                //this->setProperty(names[i].c_str(), msec_time);
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

    // Signal data update for front end
    emit dataChanged();
    // Signal to get new data
    emit getData();
}
