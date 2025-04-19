/**
 * @file SpriteRenderer.cpp
 * @brief Manages 2D sprite rendering, texture loading, and caching.
 *
 * @ingroup RenderingSystem
 *
 * Provides high-performance texture management with caching to avoid duplicate loads.
 * Wraps SFML's sprite drawing system and exposes transformation controls.
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/SpriteRenderingSystem/SpriteRenderer.h"
#include "../../Include/LoggingSystem/SpriteRenderer/SpriteRendererLogger.h"
#include <stdexcept>

 // -----------------------------------------------------
 // Static Cache Definition
 // -----------------------------------------------------

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> SpriteRenderer::textureCache;

// -----------------------------------------------------
// Constructor / Destructor
// -----------------------------------------------------

/**
 * @brief Constructs a SpriteRenderer and logs its creation.
 * @param name Object context used for logging and texture ownership tracking.
 */
SpriteRenderer::SpriteRenderer(const std::string& name)
    : objectName(name), sprite(nullptr), texture(nullptr)
{
    KryptosEngine::SpriteRendererLogger::GetLogger()->info("SpriteRenderer instance created for game object: {}", objectName);
}

// -----------------------------------------------------
// Texture Management
// -----------------------------------------------------

/**
 * @brief Loads a texture from file or uses a cached version if already loaded.
 * @param texturePath Path to the texture image file.
 * @throws std::runtime_error if the texture fails to load.
 */
void SpriteRenderer::loadTexture(const std::string& texturePath)
{
    KryptosEngine::SpriteRendererLogger::GetLogger()->info("[{}] Loading texture: {}", objectName, texturePath);

    // Check if texture is cached
    auto it = textureCache.find(texturePath);
    if (it != textureCache.end())
    {
        texture = it->second;
        KryptosEngine::SpriteRendererLogger::GetLogger()->debug("[{}] Reused cached texture: {}", objectName, texturePath);
    }
    else
    {
        auto newTexture = std::make_shared<sf::Texture>();
        if (!newTexture->loadFromFile(texturePath))
        {
            KryptosEngine::SpriteRendererLogger::GetLogger()->error("[{}] Failed to load texture from: {}", objectName, texturePath);
            throw std::runtime_error("Failed to load texture from: " + texturePath);
        }

        textureCache[texturePath] = newTexture;
        texture = newTexture;

        KryptosEngine::SpriteRendererLogger::GetLogger()->debug("[{}] Successfully loaded and cached texture: {}", objectName, texturePath);
    }

    // Preserve previous texture rect if applicable
    sf::IntRect preservedRect;
    if (sprite)
    {
        preservedRect = sprite->getTextureRect();
    }
    else if (texture)
    {
        preservedRect.position = { 0, 0 };
        preservedRect.size = { static_cast<int>(texture->getSize().x), static_cast<int>(texture->getSize().y) };
    }

    sprite = std::make_unique<sf::Sprite>(*texture);
    sprite->setTextureRect(preservedRect);
}

/**
 * @brief Sets the portion of the texture to display.
 * @param rect Rectangle (in pixels) defining the sub-region of the texture.
 */
void SpriteRenderer::setTextureRect(const sf::IntRect& rect)
{
    if (sprite)
        sprite->setTextureRect(rect);
}

/**
 * @brief Resets the texture rectangle to the full texture size.
 */
void SpriteRenderer::resetTextureRect()
{
    if (sprite && texture)
    {
        sf::IntRect rect;
        rect.position = { 0, 0 };
        rect.size = { static_cast<int>(texture->getSize().x), static_cast<int>(texture->getSize().y) };
        sprite->setTextureRect(rect);
    }
}

// -----------------------------------------------------
// Transform Setters / Getters
// -----------------------------------------------------

void SpriteRenderer::setPosition(const sf::Vector2f& position)
{
    if (sprite)
        sprite->setPosition(position);
}

sf::Vector2f SpriteRenderer::getPosition() const
{
    return sprite ? sprite->getPosition() : sf::Vector2f(0.f, 0.f);
}

void SpriteRenderer::setOrigin(const sf::Vector2f& origin)
{
    if (sprite)
        sprite->setOrigin(origin);
}

void SpriteRenderer::setRotation(float angle)
{
    if (sprite)
        sprite->setRotation(sf::degrees(angle));
}

float SpriteRenderer::getRotation() const
{
    return sprite ? sprite->getRotation().asDegrees() : 0.f;
}

void SpriteRenderer::setScale(const sf::Vector2f& scale)
{
    if (sprite)
        sprite->setScale(scale);
}

sf::Vector2f SpriteRenderer::getScale() const
{
    return sprite ? sprite->getScale() : sf::Vector2f(1.f, 1.f);
}

// -----------------------------------------------------
// Drawing
// -----------------------------------------------------

/**
 * @brief Draws the sprite to the specified render target.
 * @param window SFML window or texture to render to.
 */
void SpriteRenderer::draw(sf::RenderWindow& window) const
{
    if (sprite)
        window.draw(*sprite);
}

// -----------------------------------------------------
// Cache Utilities
// -----------------------------------------------------

/**
 * @brief Clears all cached textures. Use with caution.
 */
void SpriteRenderer::clearCache()
{
    textureCache.clear();
}
