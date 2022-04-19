#include <QObject>

class controlsWrapper : public QObject
{
    public:
        explicit controlsWrapper();
    public slots: 
        void startThread();
        // need other slot for a signal
    signals:



};
