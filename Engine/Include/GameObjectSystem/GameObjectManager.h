/**
 * @file GameObjectManager.h
 * @brief Singleton manager for registration and lifecycle of all GameObject instances.
 *
 * @ingroup GameObjectSystem
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include "GameObject.h"
#include <vector>
#include <algorithm>

 /**
  * @class GameObjectManager
  * @brief Central registry for managing all active GameObjects.
  *
  * Provides global registration, unregistration, and access to all GameObject instances.
  */
class GameObjectManager
{
public:
    // -----------------------------------------------------
    // Deleted Functions (Singleton Protection)
    // -----------------------------------------------------

    GameObjectManager(const GameObjectManager&) = delete;
    GameObjectManager& operator=(const GameObjectManager&) = delete;

    // -----------------------------------------------------
    // Accessor
    // -----------------------------------------------------

    /**
     * @brief Returns the global singleton instance of the manager.
     * @return Reference to the GameObjectManager instance.
     */
    static GameObjectManager& getInstance()
    {
        static GameObjectManager instance;
        return instance;
    }

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    /**
     * @brief Registers a new GameObject instance into the system.
     * @param object Pointer to the object to register.
     */
    void registerObject(GameObject* object);

    /**
     * @brief Unregisters a GameObject instance from the system.
     * @param object Pointer to the object to remove.
     */
    void unregisterObject(GameObject* object);

    /**
     * @brief Provides access to all currently registered GameObjects.
     * @return Const reference to the internal list of GameObject pointers.
     */
    const std::vector<GameObject*>& getGameObjects() const;

    /**
     * @brief Executes `fixedUpdate` for every registered GameObject.
     * @param fixedDeltaTime Time step to pass to each object.
     */
    void fixedUpdateAll(float fixedDeltaTime);

private:
    // -----------------------------------------------------
    // Private Constructor
    // -----------------------------------------------------

    /**
     * @brief Private constructor for enforcing singleton pattern.
     */
    GameObjectManager() = default;

    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    std::vector<GameObject*> gameObjects; ///< All registered active GameObject pointers.
};
