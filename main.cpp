#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QCursor>
#include <DataProcessor/DataUnpacker.h>
#include <vector>
#include <QQmlPropertyMap>
#include <QVariant>
#include <QString>
#include <QQuickView>

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

    // Generate maximum and minimum data constants accessible to QML files
    FILE* fp = fopen("/Users/lukelvhan/sc1-driver-io/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    if(fp == 0) {
        fp = fopen("/Users/lukelvhan/sc1-driver-io/sc1-data-format/format.json", "r"); // NOTE: Windows: "rb"; non-Windows: "r"
    }

    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);

    QQmlPropertyMap maximumDataConstants;
    QQmlPropertyMap minimumDataConstants;
    for(Value::ConstMemberIterator itr = d.MemberBegin(); itr != d.MemberEnd(); ++itr) {
        const Value& arr = itr->value.GetArray();
        std::string name = itr->name.GetString();
        std::string type = arr[1].GetString();

        if (type == "float") {
            maximumDataConstants.insert(name.data(), QVariant(arr[4].GetDouble()));
            minimumDataConstants.insert(name.data(), QVariant(arr[3].GetDouble()));
        } else if (type.substr(0, 4) == "uint") {
            maximumDataConstants.insert(name.data(), QVariant(arr[4].GetUint()));
            minimumDataConstants.insert(name.data(), QVariant(arr[3].GetUint()));
        } else if (type == "char") {
            maximumDataConstants.insert(name.data(), QVariant(arr[4].GetInt()));
            minimumDataConstants.insert(name.data(), QVariant(arr[3].GetInt()));
        } else if (type == "bool") {
            maximumDataConstants.insert(name.data(), QVariant(arr[4].GetInt() > 0));
            minimumDataConstants.insert(name.data(), QVariant(arr[3].GetInt() > 0));
        }
    }

    QQmlApplicationEngine engine;
    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("backEnd", &unpacker);
    rootContext->setContextProperty("maximum" ,&maximumDataConstants);
    rootContext->setContextProperty("minimum" ,&minimumDataConstants);


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
