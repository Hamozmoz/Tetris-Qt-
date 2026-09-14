#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "GameManager.h"
#include "Tetriminomanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterSingletonInstance("Tetris",1,0,"GameManager",&GameManager::Instance());
    qmlRegisterSingletonInstance("Tetris",1,0,"TetriminoManager",&TetriminoManager::Instance());
    //I Manually Registered The Type Because It Was Not Getting Registered With The QML_ELEMENT Macro
    qmlRegisterUncreatableType<GameMatrix>("Tetris",1,0,"GameMatrix","Qml Uncreatable Type Cannot Be Created In Qml");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Tetris", "Main");

    return QGuiApplication::exec();
}
