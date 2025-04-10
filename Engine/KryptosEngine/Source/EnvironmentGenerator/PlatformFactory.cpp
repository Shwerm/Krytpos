// PlatformFactory.cpp

#include "../Include/EnvironmentGenerator/PlatformFactory.h"
#include "../Include/GameObjectSystem/GameObjectManager.h"

std::shared_ptr<Platform> PlatformFactory::Create(const std::string& name, const sf::Vector2f& position, const std::string& texturePath)
{
    auto platform = std::make_shared<Platform>(name, position, texturePath);
    GameObjectManager::getInstance().registerObject(platform.get());
    return platform;
}
