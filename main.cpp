#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "GameManager.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterSingletonInstance("Tetris",1,0,"GameManager",&GameManager::Instance());
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Tetris", "Main");

    return QGuiApplication::exec();
}
