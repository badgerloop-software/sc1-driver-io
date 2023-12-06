#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCursor>
#include <QFileInfo>
#include <QProcess>
// #include <QDir>
// #include <QRegularExpression>
#include <DataProcessor/DataUnpacker.h>
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
    DataUnpacker unpacker;

    QQmlApplicationEngine engine;
    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("backEnd", &unpacker);

    // Hide mouse cursor
    app.setOverrideCursor(QCursor(Qt::BlankCursor));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    // run the Python file sync uploader if it's been cloned
    {
        // we look for file_sync/file_sync_up/main.py in two locations to handle 
        //  different OSs and build systems
        QProcess process;
        process.setProcessChannelMode(QProcess::MergedChannels); // show the python process's stdout interleaved
        QFileInfo check_file_p1("../sc1-driver-io/file_sync/file_sync_up/main.py");
        QFileInfo check_file_p2("../solar-car-dashboard/file_sync/file_sync_up/main.py");
        if (check_file_p1.exists() && check_file_p1.isFile()) {
            process.start("python3", QStringList() << "../sc1-driver-io/file_sync/file_sync_up/main.py");
        } else if (check_file_p2.exists() && check_file_p2.isFile()) {
            process.start("python3", QStringList() << "../solar-car-dashboard/file_sync/file_sync_up/main.py");
        } else {
            qDebug()<<"\n";
            qDebug()<<"WARNING: running without file sync";
            qDebug()<<"   * Check whether you've cloned all the submodules";
            qDebug()<<"   * If that didn't work, your build output is probably in a nonstandard directory";
            qDebug()<<"\n";
        }
    }

    return app.exec();
}
