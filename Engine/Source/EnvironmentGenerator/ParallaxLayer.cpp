#include "../../Include/EnvironmentGenerator/ParallaxLayer.h"
#include <iostream>

ParallaxLayer::ParallaxLayer(const std::string& texturePath, float scrollSpeed, float windowWidth)
    : speed(scrollSpeed), width(windowWidth)
{
    if (!texture.loadFromFile(texturePath))
    {
        std::cerr << "Failed to load parallax texture: " << texturePath << std::endl;
        return;
    }

    texture.setRepeated(true);
    texture.setSmooth(false);

    sprite1.setTexture(texture);
    sprite2.setTexture(texture);

    sprite1.setPosition(sf::Vector2f(0.f, 0.f));
    sprite2.setPosition(sf::Vector2f(width, 0.f));
}

void ParallaxLayer::update(float cameraX)
{
    float offset = -cameraX * speed;
    sprite1.setPosition(sf::Vector2f(offset, sprite1.getPosition().y));
    sprite2.setPosition(sf::Vector2f(offset + width, sprite2.getPosition().y));

    wrapSprites(cameraX);
}

void ParallaxLayer::wrapSprites(float cameraX)
{
    if (sprite1.getPosition().x + width < 0)
    {
        sprite1.setPosition(sf::Vector2f(sprite2.getPosition().x + width, sprite1.getPosition().y));
    }

    if (sprite2.getPosition().x + width < 0)
    {
        sprite2.setPosition(sf::Vector2f(sprite1.getPosition().x + width, sprite2.getPosition().y));
    }
}

void ParallaxLayer::draw(sf::RenderTarget& target)
{
    target.draw(sprite1);
    target.draw(sprite2);
}
