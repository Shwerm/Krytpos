#include "../../Include/EnvironmentGenerator/ParallaxLayer.h"
#include <iostream>

ParallaxLayer::ParallaxLayer(const std::string& texturePath, float scrollSpeed, float windowWidth, float scale, float yOffset)
    : speed(scrollSpeed), width(windowWidth), scale(scale), yOffset(yOffset)
{
    if (!texture.loadFromFile(texturePath))
    {
        std::cerr << "Failed to load parallax texture: " << texturePath << std::endl;
        return;
    }

    texture.setRepeated(true);
    texture.setSmooth(false);

    sprite1 = std::make_unique<sf::Sprite>(texture);
    sprite2 = std::make_unique<sf::Sprite>(texture);

    sprite1->setScale({ scale, scale });
    sprite2->setScale({ scale, scale });

    sprite1->setPosition({ 0.f, yOffset });
    sprite2->setPosition({ width * scale, yOffset });
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

    float spriteWidth = width * scale;

    if (sprite1->getPosition().x + spriteWidth < 0.f)
    {
        sprite1->setPosition({ sprite2->getPosition().x + spriteWidth, yOffset });
    }

    if (sprite2->getPosition().x + spriteWidth < 0.f)
    {
        sprite2->setPosition({ sprite1->getPosition().x + spriteWidth, yOffset });
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
