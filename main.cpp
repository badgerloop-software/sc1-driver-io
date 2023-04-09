#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCursor>
#include <DataProcessor/DataUnpacker.h>
#include <vector>
#include <QMutex>


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
    //QMutex m;
    //QByteArray qb;
    //controlsWrapper controlsSerial(qb, m);

    QQmlApplicationEngine engine;
    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("backEnd", &unpacker);
    //rootContext->setContextProperty("controls", &controlsSerial);

    // Hide mouse cursor
    app.setOverrideCursor(QCursor(Qt::BlankCursor));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
