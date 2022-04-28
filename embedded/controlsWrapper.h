#include <QObject>
#include <vector>
#include <unistd.h>

class controlsWrapper : public QObject
{
    public:
        explicit controlsWrapper();
    public slots: 
        void startThread();
        // need other slot for a signal
    signals:

    private:
        QByteArray &bytes;
        QMutex mutex;

        std::vector<std::string> &names;
        std::vector<std::string> &types;
};
