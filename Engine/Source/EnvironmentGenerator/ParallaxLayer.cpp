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
        std::cerr << "Failed to load parallax texture: " << texturePath << std::endl;
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

    float offsetX = lockX ? cameraView.getCenter().x - (width * scale) / 2.f
        : (-cameraX * speed + xOffset);

    float offsetY = -cameraView.getCenter().y * speed + yOffset;
    float scaledWidth = width * scale;

    sprite1->setPosition({ offsetX, offsetY });

    if (repeatEnabled && sprite2)
    {
        sprite2->setPosition({ offsetX + scaledWidth, offsetY });
        wrapSprites(cameraX);
    }

    // Debug sky layer visibility
    if (speed == 0.0f && lockX)
    {
        std::cout << "[SkyLayer] PosX: " << sprite1->getPosition().x
            << " | PosY: " << sprite1->getPosition().y << "\n";
        std::cout << "           Size: " << sprite1->getGlobalBounds().size.x
            << " x " << sprite1->getGlobalBounds().size.y << "\n";
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

    // DEBUG: Bounding box for sprite1
    sf::FloatRect bounds = sprite1->getGlobalBounds();
    sf::RectangleShape debugRect;
    debugRect.setPosition(bounds.position);
    debugRect.setSize(bounds.size);
    debugRect.setFillColor(sf::Color::Transparent);
    debugRect.setOutlineColor(sf::Color::Red);
    debugRect.setOutlineThickness(2.0f);
    target.draw(debugRect);

    if (repeatEnabled && sprite2)
    {
        target.draw(*sprite2);

        sf::FloatRect bounds2 = sprite2->getGlobalBounds();
        sf::RectangleShape debugRect2;
        debugRect2.setPosition(bounds2.position);
        debugRect2.setSize(bounds2.size);
        debugRect2.setFillColor(sf::Color::Transparent);
        debugRect2.setOutlineColor(sf::Color::Green);
        debugRect2.setOutlineThickness(2.0f);
        target.draw(debugRect2);
    }
}


