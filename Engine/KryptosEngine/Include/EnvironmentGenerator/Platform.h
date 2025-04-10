// Platform.hpp

#pragma once
#include "../GameObjectSystem/GameObject.h"
#include "../SpriteRenderingSystem/SpriteRenderer.h"
#include <memory>

class Platform : public GameObject {
public:
    Platform(const std::string& name, const sf::Vector2f& position, const std::string& texturePath);

    void draw(sf::RenderWindow& window);

private:
    std::unique_ptr<SpriteRenderer> renderer;
};
