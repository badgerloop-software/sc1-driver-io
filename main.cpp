#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <back2frontlink.h>
#include <vector>


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
    DataUnpacker unpack;

    QQmlApplicationEngine engine;
    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("backEnd", &unpack);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
