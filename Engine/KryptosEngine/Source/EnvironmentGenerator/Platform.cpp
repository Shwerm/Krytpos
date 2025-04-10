// Platform.cpp

#include "../../Include/EnvironmentGenerator/Platform.h"

Platform::Platform(const std::string& name, const sf::Vector2f& position, const std::string& texturePath)
    : GameObject(name, position, true, sf::degrees(0), 0.0f, false)
{
    renderer = std::make_unique<SpriteRenderer>(name);
    renderer->loadTexture(texturePath);
    renderer->setPosition(position);

    useGravity = false;

    addCollider({ 32.f, 7.f }, {0.f, 5.f});
}

void Platform::draw(sf::RenderWindow& window)
{
    if (renderer)
        renderer->draw(window);

    bool showColliders = true;
    if (showColliders && hasCollider())
        getCollider()->drawDebug(window);
}
