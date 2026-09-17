#include "GameManager.h"
#include "Tetriminomanager.h"

void GameManager::changeGamePaused(){
    GamePaused = !GamePaused;
    GamePausedChanged();
    if(GamePaused){
    TetriminoManager::Instance().TetriminoTimer->stop();
    TetriminoManager::Instance().FrameTimer->stop();
    }else{
        TetriminoManager::Instance().FrameTimer->start();
    }

}

GameManager &GameManager::Instance() {
    static GameManager manager;
    return manager;
}

void GameManager::ChangeGameState(GameState State){
    if(CurrentGameState != State){
        CurrentGameState = State;
        emit GameStateChanged();
    }
}

const bool GameManager::readDebugMode() const{
    return DebugMode;
}

const bool GameManager::readGamePaused() const {
    return GamePaused;
}

GameManager::GameState GameManager::GetGameState(){
    return CurrentGameState;
}


GameManager::GameManager() {
#ifndef NDEBUG
    DebugMode = true;
#endif
}






