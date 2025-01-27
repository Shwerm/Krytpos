/*
 * GameObjectManager.cpp - Kryptos Game Object Management Implementation
 * ---------------------------------------------------------------------
 * Implements the GameObjectManager class for managing game objects.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - GameObjectManager.h: Header for the GameObjectManager class.
 */

#include "../Include/GameObjectSystem/GameObjectManager.h"

 /**
  * @brief Registers a new game object.
  *
  * Adds the game object to the internal list if it is not already registered.
  * Ensures no duplicate registrations.
  * @param object Pointer to the game object to register.
  */
void GameObjectManager::registerObject(GameObject* object) {
    if (std::find(gameObjects.begin(), gameObjects.end(), object) == gameObjects.end()) {
        gameObjects.push_back(object);
    }
}

/**
 * @brief Unregisters an existing game object.
 *
 * Removes the game object from the internal list if it exists.
 * @param object Pointer to the game object to unregister.
 */
void GameObjectManager::unregisterObject(GameObject* object) {
    gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), object), gameObjects.end());
}

/**
 * @brief Provides access to all registered game objects.
 *
 * Returns a constant reference to the internal list of game objects.
 * @return A constant reference to the vector of game object pointers.
 */
const std::vector<GameObject*>& GameObjectManager::getGameObjects() const {
    return gameObjects;
}
