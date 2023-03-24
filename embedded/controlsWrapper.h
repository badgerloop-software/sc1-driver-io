#ifndef CONTROLSWRAPPER_H
#define CONTROLSWRAPPER_H

#include <QObject>
#include <QByteArray>
#include <QMutex>

class controlsWrapper : public QObject
{
    Q_OBJECT
    public:
        explicit controlsWrapper(QByteArray &bytes, QMutex &mutex, std::atomic<bool> &restart_enable, QObject *parent = nullptr);
    public slots:
        void startThread();
        // need other slot for a signal
    private:
        QByteArray &bytes;
        QMutex &mutex;
        std::atomic<bool> &restart_enable;
};

#endif
