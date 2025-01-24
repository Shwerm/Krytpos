#include "../Include/GameObjectSystem/GameObjectManager.h"

void GameObjectManager::registerObject(GameObject* object) {
    if (std::find(gameObjects.begin(), gameObjects.end(), object) == gameObjects.end()) {
        gameObjects.push_back(object);
    }
}

void GameObjectManager::unregisterObject(GameObject* object) {
    gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), object), gameObjects.end());
}

const std::vector<GameObject*>& GameObjectManager::getGameObjects() const {
    return gameObjects;
}
