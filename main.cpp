#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <DataProcessor/DataUnpacker.h>
#include <vector>
#include "embedded/devices/include/tca6416.h"


int main(int argc, char *argv[])
{
//#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//#endif

    /*argc = 3;
    argv[0] = (char*)"Appname";
    argv[1] = (char*)"--platform";
    argv[2] = (char*)"android:dpiawareness=0";*/
    QGuiApplication app(argc, argv);
    DataUnpacker unpacker;

    QQmlApplicationEngine engine;
    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("backEnd", &unpacker);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();

    // tca6416 test
    uint8_t directions[] = {1,1,1,1,1,1,1,1,1,  // assuming 1
                            1,1,1,1,1,1,1,1,1}; // is output
    Tca6416 dut(2,0x21);
    dut.begin(directions);
    while(true) {
      for (int i=0;i<8;i++) { dut.set_state(true,i,true); dut.set_state(false,i,true); }
      usleep(500000);
      for (int i=0;i<8;i++) { dut.set_state(true,i,false); dut.set_state(false,i,false); }
    }
}
