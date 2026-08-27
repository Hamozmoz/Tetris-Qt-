#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QObject>
#include <QQmlEngine>
#include "GameMatrix.h"
class GameManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* GameGrid READ getGameGrid CONSTANT)
public:
   static GameManager& Instance ();
    GameMatrix GameGrid;
    GameMatrix* getGameGrid();
private:
    GameManager();
};

#endif // GAMEMANAGER_H
