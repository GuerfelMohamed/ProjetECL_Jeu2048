#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "modelgrille.h"

int main(int argc, char *argv[])
{
    modelgrille model;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.rootContext()->setContextProperty("modelgrille", &model);// use model as property in qml under the name "modelgrille"

    engine.load(url);

    return app.exec();
}
