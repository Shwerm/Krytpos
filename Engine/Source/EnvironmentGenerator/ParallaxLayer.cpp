#include "../../Include/EnvironmentGenerator/ParallaxLayer.h"
#include <iostream>

ParallaxLayer::ParallaxLayer(const std::string& texturePath,
    float scrollSpeed,
    float windowWidth,
    float scale,
    float yOffset,
    float xOffset,
    bool repeat,
    bool lockX)
    : speed(scrollSpeed), width(windowWidth), scale(scale),
    yOffset(yOffset), xOffset(xOffset),
    repeatEnabled(repeat), lockX(lockX)
{
    if (!texture.loadFromFile(texturePath))
    {
        std::cerr << "[ERROR] Failed to load parallax texture: " << texturePath << std::endl;
        return;
    }

    texture.setRepeated(true);
    texture.setSmooth(false);

    sprite1 = std::make_unique<sf::Sprite>(texture);
    sprite1->setScale({ scale, scale });

    if (repeatEnabled)
    {
        sprite2 = std::make_unique<sf::Sprite>(texture);
        sprite2->setScale({ scale, scale });
    }
}

void ParallaxLayer::update(float cameraX, const sf::View& cameraView)
{
    if (!sprite1) return;

    float textureWidth = texture.getSize().x * scale;

    float offsetX = lockX
        ? cameraView.getCenter().x - textureWidth / 2.f
        : (-cameraX * speed + xOffset);

    float offsetY = -cameraView.getCenter().y * speed + yOffset;

    sprite1->setPosition({ offsetX, offsetY });

    if (repeatEnabled && sprite2)
    {
        sprite2->setPosition({ offsetX + textureWidth, offsetY });
        wrapSprites(cameraX, cameraView.getSize().x);
    }
}

void ParallaxLayer::wrapSprites(float cameraX, float viewWidth)
{
    if (!sprite1 || !sprite2 || lockX) return;

    float spriteWidth = texture.getSize().x * scale;
    float cameraLeft = cameraX - viewWidth / 2.f;

    if (sprite1->getPosition().x + spriteWidth < cameraLeft)
    {
        sprite1->setPosition({ sprite2->getPosition().x + spriteWidth, sprite1->getPosition().y });
    }

    if (sprite2->getPosition().x + spriteWidth < cameraLeft)
    {
        sprite2->setPosition({ sprite1->getPosition().x + spriteWidth, sprite2->getPosition().y });
    }
}

void ParallaxLayer::draw(sf::RenderTarget& target)
{
    if (!sprite1)
    {
        std::cerr << "[ParallaxLayer] Skipped draw: sprite1 not initialised.\n";
        return;
    }

    target.draw(*sprite1);

    if (repeatEnabled && sprite2)
    {
        target.draw(*sprite2);
    }
}
