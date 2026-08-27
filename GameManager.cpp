#include "GameManager.h"

GameManager &GameManager::Instance() {
    static GameManager manager;
    return manager;
}

GameMatrix *GameManager::getGameGrid(){
    return &GameGrid;
}

GameManager::GameManager() {}
