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

    // This is the only legal way to create sprites in your SFML build
    sprite1 = std::make_unique<sf::Sprite>(texture);
    sprite2 = std::make_unique<sf::Sprite>(texture);

    sprite1->setPosition({ 0.f, 0.f });
    sprite2->setPosition({ width, 0.f });
}

void ParallaxLayer::update(float cameraX)
{
    if (!sprite1 || !sprite2) return;

    float offset = -cameraX * speed;
    sprite1->setPosition({ offset, sprite1->getPosition().y });
    sprite2->setPosition({ offset + width, sprite2->getPosition().y });

    wrapSprites(cameraX);
}

void ParallaxLayer::wrapSprites(float cameraX)
{
    if (!sprite1 || !sprite2) return;

    if (sprite1->getPosition().x + width < 0.f)
    {
        sprite1->setPosition({ sprite2->getPosition().x + width, sprite1->getPosition().y });
    }

    if (sprite2->getPosition().x + width < 0.f)
    {
        sprite2->setPosition({ sprite1->getPosition().x + width, sprite2->getPosition().y });
    }
}

void ParallaxLayer::draw(sf::RenderTarget& target)
{
    if (!sprite1 || !sprite2)
    {
        std::cerr << "[ParallaxLayer] Skipped draw: sprite(s) not initialised.\n";
        return;
    }

    target.draw(*sprite1);
    target.draw(*sprite2);
}
