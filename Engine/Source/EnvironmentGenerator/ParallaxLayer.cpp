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

    sprite1.setPosition(0.f, 0.f);
    sprite2.setPosition(width, 0.f);
}

void ParallaxLayer::update(float cameraX)
{
    float offset = -cameraX * speed;
    sprite1.setPosition(offset, sprite1.getPosition().y);
    sprite2.setPosition(offset + width, sprite2.getPosition().y);

    wrapSprites(cameraX);
}

void ParallaxLayer::wrapSprites(float cameraX)
{
    float offset = -cameraX * speed;

    if (sprite1.getPosition().x + width < 0)
        sprite1.setPosition(sprite2.getPosition().x + width, sprite1.getPosition().y);

    if (sprite2.getPosition().x + width < 0)
        sprite2.setPosition(sprite1.getPosition().x + width, sprite2.getPosition().y);
}

void ParallaxLayer::draw(sf::RenderTarget& target)
{
    target.draw(sprite1);
    target.draw(sprite2);
}
