/*
 * GameObjectManager.h - Kryptos Game Object Management
 * ----------------------------------------------------
 * Manages all active game objects within the game engine.
 * Provides a singleton interface for registering, unregistering,
 * and accessing game objects.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - GameObject.h: Base class for game objects.
 *   - vector: For storing game object pointers.
 *   - algorithm: For handling object removal.
 */

#pragma once
#include "GameObject.h"
#include <vector>
#include <algorithm>

 /**
  * @class GameObjectManager
  * @brief Singleton class for managing all active game objects.
  *
  * This class provides centralized management for game objects,
  * ensuring consistent registration, unregistration, and access.
  */
class GameObjectManager {
private:
    std::vector<GameObject*> gameObjects; ///< List of all active game objects.

    /**
     * @brief Private constructor to enforce singleton pattern.
     */
    GameObjectManager() = default;

public:
    /**
     * @brief Deleted copy constructor to prevent copying the singleton instance.
     */
    GameObjectManager(const GameObjectManager&) = delete;

    /**
     * @brief Deleted assignment operator to prevent copying the singleton instance.
     */
    GameObjectManager& operator=(const GameObjectManager&) = delete;

    /**
     * @brief Provides access to the singleton instance of GameObjectManager.
     * @return A reference to the singleton instance.
     */
    static GameObjectManager& getInstance() {
        static GameObjectManager instance;
        return instance;
    }

    /**
     * @brief Registers a new game object.
     *
     * Adds the object to the internal list if it is not already registered.
     * @param object Pointer to the game object to register.
     */
    void registerObject(GameObject* object);

    /**
     * @brief Unregisters an existing game object.
     *
     * Removes the object from the internal list.
     * @param object Pointer to the game object to unregister.
     */
    void unregisterObject(GameObject* object);

    /**
     * @brief Provides access to all registered game objects.
     * @return A constant reference to the vector of game object pointers.
     */
    const std::vector<GameObject*>& getGameObjects() const;
};
