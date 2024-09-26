#include "DTI.h"
#include <thread>
#include <QSerialPort>
#include <QTimer>
#include <QSocketNotifier>

class Serial : public DTI {
public:
    Serial(QString SerialDevice) {
        // Initialize serial port with the provided device name
        device = SerialDevice;
        serial.setPortName(SerialDevice);

        // Set Baud rate, Data bits, Parity, Stop bits, and Flow control
        serial.setBaudRate(QSerialPort::Baud115200);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);

        // Connect readyRead signal to a slot for reading incoming data
        connect(&serial, &QSerialPort::readyRead, this, &Serial::readData);

        // Connect errorOccurred signal to handle errors, such as device unplugged
        connect(&serial, QOverload<QSerialPort::SerialPortError>::of(&QSerialPort::errorOccurred),
                this, &Serial::handleError);

        // Setup timer for checking serial port status and reconnecting if necessary
        connect(&reconnectTimer, &QTimer::timeout, this, &Serial::checkConnection);
        reconnectTimer.start(5000); // Check every 5 seconds
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
        int returnCode = serial.write(bytes);
        if (returnCode == -1) {
            qDebug()<<"Error occurred send data";
            serial.close();
        }
        serial.flush();
    }

private slots:
    void readData() {
        // Read data from the serial port when data is available
        QByteArray data = serial.readAll();
        // Process the received data as needed
        processReceivedData(data);
    }

    void checkConnection() {
        if (!serial.isOpen()) {
            qDebug() << "Serial port disconnected. Reconnecting...";
            serial.close();
            serial.open(QIODevice::ReadWrite);
            if (!serial.isOpen()) {
                qDebug() << "Failed to reconnect to serial port";
            }
        } else {
            qDebug() << "Still open";
        }
    }

    void handleError(QSerialPort::SerialPortError error) {
        if (error == QSerialPort::ResourceError) {
            qDebug() << "Serial port error occurred. Reconnecting...";
            // Attempt to reconnect
            serial.close();
            serial.open(QIODevice::ReadWrite);
            if (!serial.isOpen()) {
                qDebug() << "Failed to reconnect to serial port";
            }
        }
    }

private:
    QSerialPort serial;
    QString device;
    QTimer reconnectTimer;

    void processReceivedData(const QByteArray &data) {
        // Implement your data processing logic here
        qDebug() << "Received data:" << data;
    }
};
