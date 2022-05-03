#ifndef CONTROLSWRAPPER_H
#define CONTROLSWRAPPER_H

#include <QObject>
#include <vector>
#include <unistd.h>
#include <QMutex>

class controlsWrapper : public QObject
{
    public:
        explicit controlsWrapper(QByteArray &bytes, std::vector<std::string> &names, std::vector<std::string> &types, QMutex &mutex, QObject *parent = nullptr);
    public slots: 
        void startThread();
        // need other slot for a signal
    signals:
        void dataReady();
    private:
        void addFloatToArray(QByteArray &dataArr, float data);

        QByteArray &bytes;
        QMutex &mutex;

        std::vector<std::string> &names;
        std::vector<std::string> &types;
};

#endif // CONTROLSWRAPPER_H
