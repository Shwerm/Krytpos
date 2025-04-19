/**
 * @file ParallaxLayer.cpp
 * @brief Implementation of a single scrolling parallax layer for depth effect.
 *
 * @ingroup RenderingSystem
 *
 * Loads a texture and creates one or two sprites depending on whether it should repeat horizontally.
 * Handles camera-relative movement and seamless horizontal wrapping if enabled.
 *
 * Used by ParallaxBackground to create visual depth across a 2D scene.
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/EnvironmentGenerator/ParallaxLayer.h"
#include <iostream>

 // -----------------------------------------------------
 // Constructor
 // -----------------------------------------------------

 /**
  * @brief Constructs a ParallaxLayer with full scroll and positioning behaviour.
  * @param texturePath Path to the background texture.
  * @param scrollSpeed Multiplier for how fast the layer scrolls relative to the camera.
  * @param windowWidth Used for wrapping logic if repeating is enabled.
  * @param scale Sprite scale factor.
  * @param yOffset Vertical offset from the view center.
  * @param xOffset Horizontal scroll offset.
  * @param repeat Whether the layer should repeat horizontally.
  * @param lockX If true, layer does not scroll horizontally (sky layer).
  */
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

// -----------------------------------------------------
// Public Methods
// -----------------------------------------------------

/**
 * @brief Updates the sprite positions based on camera X position and view.
 * @param cameraX Camera’s world-space X coordinate.
 * @param cameraView The current SFML view for screen-centred offsets.
 */
void ParallaxLayer::update(float cameraX, const sf::View& cameraView)
{
    if (!sprite1) return;

    float textureWidth = texture.getSize().x * scale;

    // X and Y offset based on scroll speed and view
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

/**
 * @brief Wraps horizontally repeating sprites to stay within view as the camera scrolls.
 * @param cameraX The X position of the camera.
 * @param viewWidth The width of the view used for bounds detection.
 */
void ParallaxLayer::wrapSprites(float cameraX, float viewWidth)
{
    if (!sprite1 || !sprite2 || lockX) return;

    float spriteWidth = texture.getSize().x * scale;
    float camLeft = cameraX - viewWidth / 2.f;
    float camRight = cameraX + viewWidth / 2.f;

    // Left wrap
    if (sprite1->getPosition().x + spriteWidth < camLeft)
    {
        sprite1->setPosition({ sprite2->getPosition().x + spriteWidth, sprite1->getPosition().y });
    }
    else if (sprite2->getPosition().x + spriteWidth < camLeft)
    {
        sprite2->setPosition({ sprite1->getPosition().x + spriteWidth, sprite2->getPosition().y });
    }

    // Right wrap
    if (sprite1->getPosition().x > camRight)
    {
        sprite1->setPosition({ sprite2->getPosition().x - spriteWidth, sprite1->getPosition().y });
    }
    else if (sprite2->getPosition().x > camRight)
    {
        sprite2->setPosition({ sprite1->getPosition().x - spriteWidth, sprite2->getPosition().y });
    }
}

/**
 * @brief Draws one or both sprites to the given render target.
 * @param target The render target (e.g., window or texture).
 */
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
