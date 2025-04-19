/**
 * @file PlatformFactory.cpp
 * @brief Implementation of the PlatformFactory responsible for platform instantiation and registration.
 *
 * @ingroup EnvironmentSystem
 *
 * Provides a simple interface for creating and registering platform instances.
 * Used heavily by the EnvironmentGenerator and procedural level logic.
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/EnvironmentGenerator/PlatformFactory.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"

 // -----------------------------------------------------
 // Static Methods
 // -----------------------------------------------------

 /**
  * @brief Creates a shared pointer to a Platform, registers it with the GameObjectManager, and returns it.
  * @param name Unique name for the platform object.
  * @param position Spawn position in world coordinates.
  * @param texturePath Path to the platform’s sprite texture.
  * @return A shared_ptr to the newly created Platform.
  */
std::shared_ptr<Platform> PlatformFactory::Create(const std::string& name, const sf::Vector2f& position, const std::string& texturePath)
{
    auto platform = std::make_shared<Platform>(name, position, texturePath);
    GameObjectManager::getInstance().registerObject(platform.get());
    return platform;
}
