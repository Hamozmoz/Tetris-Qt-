#include "GameManager.h"

GameManager &GameManager::Instance() {
    static GameManager manager;
    return manager;
}


GameManager::GameManager() {}
