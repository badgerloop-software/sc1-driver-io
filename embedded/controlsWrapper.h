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
        void lockMutex();
        void unlockMutex();
        void addFloatToArray(QByteArray *dataArr, float data);

        QByteArray *bytes;
        QMutex *mutex;

        std::vector<std::string> &names;
        std::vector<std::string> &types;

        /**
         * A generic function to put data into array
         * @tparam E any type of data that can use binary operand
         * @param dataArr data put into this array
         * @param data
         */
        template<typename E>
        void dataToByteArray(QByteArray *dataArr, E data) {
            for (int i = sizeof(data)-1; i >= 0 ; i--) {
                dataArr->push_back(data >> (8 * i) & 0xFF);
            }
        }
};

#endif // CONTROLSWRAPPER_H
