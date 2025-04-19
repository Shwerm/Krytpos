/**
 * @file GameObjectManager.cpp
 * @brief Manages all active GameObjects in the Kryptos Engine.
 *
 * @ingroup GameObjectSystem
 *
 * Provides centralised registration, unregistration, and iteration over all GameObjects.
 * Ensures clean lifecycle handling of runtime objects and supports fixed update propagation.
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/GameObjectSystem/GameObjectManager.h"

 // -----------------------------------------------------
 // Public Methods
 // -----------------------------------------------------

 /**
  * @brief Registers a GameObject if it's not already in the system.
  * @param object Pointer to the GameObject to add.
  */
void GameObjectManager::registerObject(GameObject* object)
{
    if (std::find(gameObjects.begin(), gameObjects.end(), object) == gameObjects.end())
    {
        gameObjects.push_back(object);
    }
}

/**
 * @brief Removes a GameObject from the registry.
 * @param object Pointer to the GameObject to remove.
 */
void GameObjectManager::unregisterObject(GameObject* object)
{
    gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), object), gameObjects.end());
}

/**
 * @brief Returns a const reference to all currently registered GameObjects.
 * @return Const vector reference of GameObject pointers.
 */
const std::vector<GameObject*>& GameObjectManager::getGameObjects() const
{
    return gameObjects;
}

/**
 * @brief Calls fixedUpdate on all registered GameObjects.
 * @param fixedDeltaTime The fixed timestep to apply.
 */
void GameObjectManager::fixedUpdateAll(float fixedDeltaTime)
{
    for (auto* object : gameObjects)
    {
        object->fixedUpdate(fixedDeltaTime);
    }
}
