#pragma once
#include "GameObject.h"
#include <vector>
#include <algorithm>

class GameObjectManager {
private:
    std::vector<GameObject*> gameObjects; // List of all active game objects

    // Private constructor for singleton
    GameObjectManager() = default;

public:
    // Delete copy constructor and assignment operator
    GameObjectManager(const GameObjectManager&) = delete;
    GameObjectManager& operator=(const GameObjectManager&) = delete;

    // Singleton instance access
    static GameObjectManager& getInstance() {
        static GameObjectManager instance;
        return instance;
    }

    // Register a new game object
    void registerObject(GameObject* object);

    // Unregister an existing game object
    void unregisterObject(GameObject* object);

    // Access all game objects
    const std::vector<GameObject*>& getGameObjects() const;
};
