#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QObject>
#include <QQmlEngine>
#include <qguiapplication.h>
class GameManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(GameState CurrentGameState READ GetGameState NOTIFY GameStateChanged)
    Q_PROPERTY(bool DebugMode READ readDebugMode CONSTANT)
    Q_PROPERTY(bool GamePaused READ readGamePaused NOTIFY GamePausedChanged)
public:
    enum GameState{
        OpeningScreen,
        GameRunning
    };
    Q_ENUM(GameState)
    Q_INVOKABLE void changeGamePaused();
    Q_INVOKABLE void quitGame();
    GameState CurrentGameState = GameState::OpeningScreen;
   static GameManager& Instance ();
    GameState GetGameState();
    void ChangeGameState(GameState State);
    const bool readDebugMode() const;
    const bool readGamePaused() const;
signals :
void GameStateChanged();
    void GamePausedChanged();
private:
bool GamePaused{false};
bool DebugMode {false};
    GameManager();
};

#endif // GAMEMANAGER_H
