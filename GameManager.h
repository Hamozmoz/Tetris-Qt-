#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QObject>
#include <QQmlEngine>
class GameManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(GameState CurrentGameState READ GetGameState NOTIFY GameStateChanged)
public:
    enum GameState{
        OpeningScreen,
        GameRunning
    };
    Q_ENUM(GameState)
    GameState CurrentGameState = GameState::OpeningScreen;
   static GameManager& Instance ();
    GameState GetGameState(){
        return CurrentGameState;
    }
    void ChangeGameState(GameState State){
        if(CurrentGameState != State){
            CurrentGameState = State;
            emit GameStateChanged();
        }
    }
signals :
void GameStateChanged();

private:
    GameManager();
};

#endif // GAMEMANAGER_H
