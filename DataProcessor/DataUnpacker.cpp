//
// Created by Mingcan Li on 11/16/21.
//

#include "DataUnpacker.h"

double speedFunc(double t)
{
    return t*t;
}

double solarFunc(double t)
{
    return t*t*t;
}

double batteryFunc(double t)
{
    return pow(2.71828,-t)*100;
}

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
void bytesToSomethingNotDouble(QByteArray data, int startPos, int endPos, E &var)
{
    int byteNum=endPos-startPos;
    var = 0;
    for(int i = startPos ; i<=endPos ; i++) {
        var=var+data[i]<<byteNum*8;
        byteNum--;
    }
}



//DataUnpacker::DataUnpacker(unpackedData &processedData, QObject *parent) : QObject(parent), processedData(processedData)
// TODO Watch vector type for boolData
DataUnpacker::DataUnpacker(unpackedData &processedData, std::vector<float> &floatData, std::vector<char> &charData, std::vector<uint8_t> &boolData, std::vector<uint8_t> &uint8_tData, std::vector<std::string> &names, std::vector<std::string> &types, QObject *parent) : QObject(parent), processedData(processedData), floatData(floatData), charData(charData), boolData(boolData), uint8_tData(uint8_tData), names(names), types(types)// TODO Remove processedData
{
    this->processedData = processedData; // TODO
    this->floatData = floatData;
    this->uint8_tData = uint8_tData;
    this->charData = charData;
    this->boolData = boolData;
    this->names = names;
    this->types = types;


    /*QString fileContents;
    QFile file;
    file.setFileName("../sc1-data-format/format.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileContents = file.readAll();
    file.close();
    QJsonDocument d = QJsonDocument::fromJson(fileContents.toUtf8());
    format = d.object();
    // Initialize
    // TODO names = format.keys(); // TODO It's sorted lexographically
    QJsonObject::const_iterator currElement = format.begin(); // TODO It's still sorted, and there's no way around it. Look into another JSON parsing library
    QJsonObject::const_iterator end = format.end();*/

    // TODO std::string fileContents;

    /* TODO
    QFile file; // TODO Do this with standard libraries
    const char* fileContents;
    QString fileContents2;
    // TODO std::string fileContents;
    Document d;
    file.setFileName("../sc1-data-format/format.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    fileContents = file.readAll().toStdString().c_str();
    fileContents2 = file.readAll();
    //const char fileContents[] = file.readAll().toStdString().;
    // TODO fileContents = file.readAll().toStdString();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(fileContents2.toUtf8());
    format = doc.object();

    if(d.Parse(fileContents).HasParseError()) {
        speedTest = 0;
    } else {
        assert(d.IsObject());

        for(Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
            //QJsonArray currValue = currElement.value().toArray();
            std::string name = itr->name.GetString();
            const Value& arr = itr->value.GetArray();
            names.push_back(name);
            byteNums.push_back(arr[0].GetInt());
            types.push_back(arr[1].GetString());
        }

        // TODO speedTest = (int) types[20].at(0);
        speedTest = 55;
    }*/

    /*typedef GenericDocument<UTF16<> > WDocument;
    typedef GenericValue<UTF16<> > WValue;

    FILE* fp = fopen("../sc1-data-format/format.json", "r"); // non-Windows use "r"

    char readBuffer[65536];
    FileReadStream bis(fp, readBuffer, sizeof(readBuffer));

    AutoUTFInputStream<unsigned, FileReadStream> eis(bis);  // wraps bis into eis

    WDocument d;
    d.ParseStream<0, AutoUTF<unsigned> >(eis);*/


    //--------------------------------------------------------------------------------------
    // TODO rapidjson part 1

    // testing
    FILE* fp = fopen("../sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    // pi needs an absolute filepath :((((((
    // TODO add code to check if the file can be successfully read (using the relative filepath); if it fails to read the file, use the absolute path
    // ^^ Maybe try absolute first and then try relative
    // TODO FILE* fp = fopen("/absolute/file/path/here/solar-car-dashboard/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    //FILE* fp = fopen("/home/james/solar-car-dashboard/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);

    //---------------------------------------------------------------------------------------
    // TODO nlohmann

    /*
    json j;
    //std::ifstream i("../sc1-data-format/format.json");
    std::ifstream i("/home/james/solar-car-dashboard/sc1-data-format/format.json");
    i >> j;

    for (const auto& item : j.items()) {
        //std::cout << item.key() << "\n";
        std::string name = item.key();

        //const Value& arr = itr->value.GetArray();

        names.push_back(name);
        //byteNums.push_back(item[0]);
        //types.push_back(arr[1].GetString());
        int arrCount = 0;
        for(const auto& arrVal : j[name]) {
            if(arrCount == 0) {
                byteNums.push_back(arrVal);
            } else {
                types.push_back(arrVal);
            }

            arrCount++;
        }
    }*/

    //---------------------------------------------------------------------------------------

    /*std::ifstream ifs("../sc1-data-format/format.json");
    IStreamWrapper isw(ifs);

    Document d;
    d.ParseStream<0, UTF16LE<> >(isw);
    //d.ParseStream(isw);*/

    /*std::string FilePath = "../sc1-data-format/format.json";
    FILE* fp = fopen(FilePath.c_str(), "r");
    char ReadBuffer[65536];
    FileReadStream MyJsonReadStream(fp, ReadBuffer, sizeof(ReadBuffer));
    Document d;
    if(fp != NULL)
        fclose(fp);
    if (!d.ParseStream(MyJsonReadStream).HasParseError())
    {*/

    //--------------------------------------------------------------------------------------
    // TODO rapidjson part 2

    for(Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
        std::string name = itr->name.GetString();
        const Value& arr = itr->value.GetArray();
        names.push_back(name);
        byteNums.push_back(arr[0].GetInt());
        types.push_back(arr[1].GetString());
    }

    fclose(fp);
    //delete fp;

    //--------------------------------------------------------------------------------------

    //speedTest = byteNums[10];
    //speedTest = (int) names[3].at(0); // TODO
    /* TODO
    for(const QString& i : names) {
        QJsonArray currValue = format[i].toArray();
        byteNums.push_back(currValue[0].toInt());
        types.push_back(currValue[1].toString());
    }*/
    /* TODO
    int eCount = 0;
    while((currElement != end)) {// || (eCount >= 3)) {
        QJsonArray currValue = currElement.value().toArray();
        names.push_back(currElement.key());
        byteNums.push_back(currValue[0].toInt());
        types.push_back(currValue[1].toString());
        currElement++;
        eCount ++;
    }*/
    //QJsonArray value = format["solarPower"].toArray();
    //QJsonArray value = format.value(QString("speed")).toArray();
    //QJsonObject item = value.toObject();
    //QJsonArray test = value["imp"].toArray();
    //speedTest = value[0].toInt();

    // TODO speedTest = types[20].at(0).unicode(); // TODO It's still sorted, and there's no way around it. Look into another JSON parsing library
    speedTest = byteNums[2]; // TODO

    time = 0; // TODO it would probably be best to include timestamps in the TCP payloads (wouldn't need to add them to the format)

    // TODO Create the following arrays using format.json: keys/names, numBytes, types (as strings)
    // TODO Probably also create arrays for bools, chars, uint8_ts, and floats
    // TODO Actually, pass the arrays (concerning the data, not necessarily names/numBytes/types, or at least probably not types, maybe numBytes and names) to DataUnpacker by references
    /* TODO
    std::vector<std::string> names;
    std::vector<uint8_t> sizes;
    std::vector<std::string> types;*/
}

/*DataUnpacker::~DataUnpacker()
{
    emit finished();
}*/

void DataUnpacker::onNewConnection()
{
   QTcpSocket *clientSocket = _server.nextPendingConnection();
   connect(clientSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
   connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(onSocketStateChanged(QAbstractSocket::SocketState)));

    _sockets.push_back(clientSocket);
    /*for (QTcpSocket* socket : _sockets) {
        socket->write(QByteArray::fromStdString("From solar car: " + clientSocket->peerAddress().toString().toStdString() + " connected to server !\n"));
    }*/
}

void DataUnpacker::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
        _sockets.removeOne(sender);
    }
}

void DataUnpacker::onReadyRead()
{
    QTcpSocket* sender = static_cast<QTcpSocket*>(QObject::sender());
    QByteArray datas = sender->readAll();
    for (QTcpSocket* socket : _sockets) {
        if (socket != sender)
            socket->write(QByteArray::fromStdString(sender->peerAddress().toString().toStdString() + ": " + datas.toStdString()));
    }
}

void DataUnpacker::unpack(QByteArray rawData)
{
    // TODO Definitely handle this using a for loop and the arrays created in constructor using format.json
    int currByte = 0;
    uint numFloats = 0;
    uint numUint8_ts = 0;
    uint numChars = 0;
    uint numBools = 0;
    // TODO Probably clear() in threadProcedure and then just use size()s

    for(uint i=0; i < names.size(); i++) {
        if(types[i] == "float") {
            if(floatData.size() == numFloats) {
                floatData.push_back(0.0f);
            }
            floatData[numFloats] = bytesToFloat(rawData, currByte);
            //Incorrect floatData[floatData.size()] = bytesToFloat(rawData, currByte);
            numFloats++;
        } else if(types[i] == "uint8") {
            if(uint8_tData.size() == numUint8_ts) {
                uint8_tData.push_back(0);
            }
            bytesToSomethingNotDouble(rawData, currByte, currByte + byteNums[i] - 1, uint8_tData[numUint8_ts]);
            //Incorrect bytesToSomethingNotDouble(rawData, currByte, currByte + byteNums[i] - 1, uint8_tData[uint8_tData.size()]);
            numUint8_ts++;
        } else if(types[i] == "bool") {
            if(boolData.size() == numBools) {
                boolData.push_back(false);
            }
            bytesToSomethingNotDouble(rawData, currByte, currByte + byteNums[i] - 1, boolData[numBools]);
            //Incorrect bytesToSomethingNotDouble(rawData, currByte, currByte + byteNums[i] - 1, boolData[boolData.size()]);
            numBools++;
        } else if(types[i] == "char") {
            if(charData.size() == numChars) {
                charData.push_back('0');
            }
            bytesToSomethingNotDouble(rawData, currByte, currByte + byteNums[i] - 1, charData[numChars]);
            //Incorrect bytesToSomethingNotDouble(rawData, currByte, currByte + byteNums[i] - 1, charData[charData.size()]);
            numChars++;
        } else if(types[i] == "double") {
            // TODO: No double data yet; Implement when there is double data
        }
        currByte += byteNums[i];
    }
    /* TODO
    bytesToSomethingNotDouble(rawData, 0, 0, speed);
    bytesToSomethingNotDouble(rawData, 1, 1, charge);
    solarP = bytesToFloat(rawData,2);
    batteryV = bytesToFloat(rawData,6);
    batteryI = bytesToFloat(rawData,10);
    netP = bytesToFloat(rawData,14);
    motorP = bytesToFloat(rawData,18);
    bytesToSomethingNotDouble(rawData,22,22,state);
    batteryT = bytesToFloat(rawData,23);
    motorT = bytesToFloat(rawData,27);
    motorControllerT = bytesToFloat(rawData,31);
    bytesToSomethingNotDouble(rawData,35,35,bpsFault);
    bytesToSomethingNotDouble(rawData,36,36,eStop);
    bytesToSomethingNotDouble(rawData,37,37,cruise);
    bytesToSomethingNotDouble(rawData,38,38,lt);
    bytesToSomethingNotDouble(rawData,39,39,rt);
    bytesToSomethingNotDouble(rawData,40,40,flTp);
    bytesToSomethingNotDouble(rawData,41,41,frTp);
    bytesToSomethingNotDouble(rawData,42,42,rlTp);
    bytesToSomethingNotDouble(rawData,43,43,rrTp);
    batteryGroup1 = bytesToFloat(rawData,44);
    batteryGroup2 = bytesToFloat(rawData,48);
    batteryGroup3 = bytesToFloat(rawData,52);
    batteryGroup4 = bytesToFloat(rawData,56);*/
}


void DataUnpacker::startThread()
{
    _server.listen(QHostAddress::AnyIPv4, 4003);
    connect(&_server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));

    threadProcedure();
}

void DataUnpacker::threadProcedure()
{
    DataGen data(&speedFunc,&solarFunc,&batteryFunc,100);

    QByteArray bytes;

    /* TODO
    floatData.clear();
    charData.clear();
    boolData.clear();
    uint8_tData.clear();
    */

    data.getData(bytes, names, types, time);

    unpack(bytes);

    // TODO uint8_tData[0] = (uint8_t) uint8_tData.size();

    // TODO Could try setting up Q_PROPERTYs for each data field and loop through and set them using setProperty() w/ the names & data in the arrays created in the constructor
    // Update unpackedData struct for BackendProcesses
    // TODO Remove individual data members from DataUnpacker and use these in unpack (need to change bytesToDouble() to bytesToFloat())
    //processedData.speed = speed;
    /* TODO
    processedData.speed = speedTest;
    processedData.charge = charge;
    processedData.solarPower = solarP;
    processedData.batteryVoltage = batteryV;
    processedData.batteryCurrent = batteryI;
    processedData.netPower = netP;
    processedData.motorPower = motorP;
    processedData.state = state;
    processedData.batteryTemp = batteryT;
    processedData.motorTemp = motorT;
    processedData.motorControllerTemp = motorControllerT;
    processedData.bpsFault = bpsFault;
    processedData.eStop = eStop;
    processedData.cruiseControl = cruise;
    processedData.leftTurn = lt;
    processedData.rightTurn = rt;
    processedData.flTp = flTp;
    processedData.frTp = frTp;
    processedData.rlTp = rlTp;
    processedData.rrTp = rrTp;
    processedData.bat1 = batteryGroup1;
    processedData.bat2 = batteryGroup2;
    processedData.bat3 = batteryGroup3;
    processedData.bat4 = batteryGroup4;*/

    for (QTcpSocket* socket : _sockets) {
        //socket->write(QByteArray::fromStdString("From solar car: connected to server! " + std::to_string(time) + "\n"));
        //socket->write(QByteArray::fromStdString("Speed: " + std::to_string(speed) + "; Size: " + std::to_string(sizeof(bytes)) + "\n"));
        socket->write(bytes);
    }

    time = (time < 7) ? (time + 0.25) : 0;

    usleep(1000000 );
    emit dataReady();
}


