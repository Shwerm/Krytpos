// PlatformFactory.hpp

#pragma once
#include "../EnvironmentGenerator/Platform.h"
#include <memory>

class PlatformFactory {
public:
    static std::shared_ptr<Platform> Create(const std::string& name, const sf::Vector2f& position, const std::string& texturePath);
};
