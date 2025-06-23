#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "controller.h"
#include "model.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Model* model = new Model(0, 32, 237.15);
    Controller* controller = new Controller(model);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("model", model);
    engine.rootContext()->setContextProperty("controller", controller);
    engine.loadFromModule("zad6", "Main");

    return app.exec();
}
