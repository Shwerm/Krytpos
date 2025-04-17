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
    sprite1->setColor(sf::Color(255, 255, 255, 255)); // ensure visibility

    std::cout << "[DEBUG] Loaded texture: " << texturePath << "\n";
    std::cout << "        Texture size: " << texture.getSize().x << " x " << texture.getSize().y << "\n";

    if (repeatEnabled)
    {
        sprite2 = std::make_unique<sf::Sprite>(texture);
        sprite2->setScale({ scale, scale });
        sprite2->setColor(sf::Color(255, 255, 255, 255));
    }
}

void ParallaxLayer::update(float cameraX, const sf::View& cameraView)
{
    if (!sprite1) return;

    // FIX: Use texture width instead of window width
    float offsetX = lockX
        ? cameraView.getCenter().x - (texture.getSize().x * scale) / 2.f
        : (-cameraX * speed + xOffset);

    float offsetY = -cameraView.getCenter().y * speed + yOffset;
    float scaledWidth = width * scale;

    sprite1->setPosition({ offsetX, offsetY });

    /*if (lockX && speed == 0.0f)
    {
        std::cout << "[DEBUG] Sky sprite Pos: " << sprite1->getPosition().x << ", " << sprite1->getPosition().y << "\n";
        std::cout << "         Size: " << sprite1->getGlobalBounds().size.x << " x " << sprite1->getGlobalBounds().size.y << "\n";
    }*/

    if (repeatEnabled && sprite2)
    {
        sprite2->setPosition({ offsetX + scaledWidth, offsetY });
        wrapSprites(cameraX);
    }
}

void ParallaxLayer::wrapSprites(float cameraX)
{
    if (!sprite1 || !sprite2 || lockX) return;

    float spriteWidth = width * scale;

    if (sprite1->getPosition().x + spriteWidth < 0.f)
    {
        sprite1->setPosition({ sprite2->getPosition().x + spriteWidth, sprite1->getPosition().y });
    }

    if (sprite2->getPosition().x + spriteWidth < 0.f)
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
