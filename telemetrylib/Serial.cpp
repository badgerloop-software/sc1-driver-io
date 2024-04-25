#include "DTI.h"
#include <thread>
#include <QSerialPort>

class Serial : public DTI {
public:
    Serial(QString SerialDevice) {
        // Initialize serial port with the provided device name
        serial.setPortName(SerialDevice);

        // Open the serial port in ReadWrite mode
        if (!serial.open(QIODevice::ReadWrite)) {
            qDebug() << "Failed to open serial port" << SerialDevice;
            return;
        }

        // Set Baud rate, Data bits, Parity, Stop bits, and Flow control
        serial.setBaudRate(QSerialPort::Baud115200);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);

        // Connect readyRead signal to a slot for reading incoming data
        connect(&serial, &QSerialPort::readyRead, this, &Serial::readData);
    }

    ~Serial() {
        // Close the serial port upon destruction
        serial.close();
    }

    void sendData(QByteArray bytes, long long timestamp) override {
        qDebug()<<"sending via Serial";
        bytes.push_front("<bsr>");
        bytes.push_back("</bsr>");
        // Write data to the serial port
        serial.write(bytes);
        // You might want to use timestamp for something
    }

private slots:
    void readData() {
        // Read data from the serial port when data is available
        QByteArray data = serial.readAll();
        // Process the received data as needed
        processReceivedData(data);
    }

private:
    QSerialPort serial;

    void processReceivedData(const QByteArray &data) {
        // Implement your data processing logic here
        qDebug() << "Received data:" << data;
    }
};
