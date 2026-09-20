#include "GameManager.h"
#include "Tetriminomanager.h"
#include <fstream>
#include <filesystem>
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

void GameManager::quitGame(){
WriteToDataFile();
    QGuiApplication::exit();
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

const uint GameManager::readHighScore() const {
    return HighScore;
}

GameManager::GameState GameManager::GetGameState(){
    return CurrentGameState;
}


GameManager::GameManager() {
#ifndef NDEBUG
    DebugMode = true;
#endif
ReadDataFile();
}

void GameManager::ReadDataFile()
{
uint scoreinfile{0};
if(std::filesystem::exists("Data.txt")){
std::ifstream file;
file.open("Data.txt");
file.read(reinterpret_cast<char*>(&scoreinfile),sizeof(scoreinfile));
if(scoreinfile > HighScore){
HighScore = scoreinfile;
}
file.close();
}

}

void GameManager::WriteToDataFile(){
    std::ofstream file("Data.txt",std::ios::binary);
  file.write(reinterpret_cast<char*>(&HighScore),sizeof(HighScore));
  file.close();
}






