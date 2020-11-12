#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <tcp_json.h>

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    TCP_Json connection;;    //creating core app
    QQmlContext *context = engine.rootContext();    //creating root context
    context->setContextProperty("connection", &connection);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
