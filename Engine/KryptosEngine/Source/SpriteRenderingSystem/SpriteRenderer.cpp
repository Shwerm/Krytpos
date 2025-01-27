/*
 * SpriteRenderer.cpp - Kryptos Sprite Rendering System Implementation
 * -------------------------------------------------------------------
 * Implements the SpriteRenderer class for managing sprites and textures.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - SpriteRenderer.h: Header for the SpriteRenderer class.
 *   - stdexcept: For exception handling.
 */

#include "../Include/SpriteRenderingSystem/SpriteRenderer.h"
#include <stdexcept>

 // Initialize the static texture cache
std::unordered_map<std::string, std::shared_ptr<sf::Texture>> SpriteRenderer::textureCache;

/**
 * @brief Constructs a SpriteRenderer object.
 * Initializes the sprite and texture pointers to nullptr.
 */
SpriteRenderer::SpriteRenderer() : sprite(nullptr), texture(nullptr) {}

/**
 * @brief Loads a texture from a file and sets it for the sprite.
 *
 * If the texture is already cached, it reuses the cached instance. Otherwise, it loads
 * the texture from the specified file and stores it in the cache.
 * @param texturePath The file path of the texture to load.
 * @throws std::runtime_error If the texture cannot be loaded.
 */
void SpriteRenderer::loadTexture(const std::string& texturePath) {
    auto it = textureCache.find(texturePath);
    if (it != textureCache.end()) {
        texture = it->second;
    }
    else {
        auto newTexture = std::make_shared<sf::Texture>();
        if (!newTexture->loadFromFile(texturePath)) {
            throw std::runtime_error("Failed to load texture from: " + texturePath);
        }
        textureCache[texturePath] = newTexture;
        texture = newTexture;
    }

    sprite = std::make_unique<sf::Sprite>(*texture);
}

/**
 * @brief Sets the position of the sprite.
 * @param position The new position of the sprite.
 */
void SpriteRenderer::setPosition(const sf::Vector2f& position) {
    if (sprite) {
        sprite->setPosition(position);
    }
}

/**
 * @brief Gets the position of the sprite.
 * @return The position of the sprite as a vector.
 */
sf::Vector2f SpriteRenderer::getPosition() const {
    return sprite ? sprite->getPosition() : sf::Vector2f(0.f, 0.f);
}

/**
 * @brief Sets the origin of the sprite for transformations.
 * @param origin The new origin of the sprite.
 */
void SpriteRenderer::setOrigin(const sf::Vector2f& origin) {
    if (sprite) {
        sprite->setOrigin(origin);
    }
}

/**
 * @brief Sets the rotation of the sprite.
 * @param angle The rotation angle in degrees.
 */
void SpriteRenderer::setRotation(float angle) {
    if (sprite) {
        sprite->setRotation(sf::degrees(angle));
    }
}

/**
 * @brief Gets the current rotation of the sprite.
 * @return The rotation angle in degrees.
 */
float SpriteRenderer::getRotation() const {
    return sprite ? sprite->getRotation().asDegrees() : 0.f;
}

/**
 * @brief Sets the scale of the sprite.
 * @param scale The new scale of the sprite as a vector.
 */
void SpriteRenderer::setScale(const sf::Vector2f& scale) {
    if (sprite) {
        sprite->setScale(scale);
    }
}

/**
 * @brief Gets the current scale of the sprite.
 * @return The scale of the sprite as a vector.
 */
sf::Vector2f SpriteRenderer::getScale() const {
    return sprite ? sprite->getScale() : sf::Vector2f(1.f, 1.f);
}

/**
 * @brief Renders the sprite to the specified render window.
 * @param window The render window where the sprite will be drawn.
 */
void SpriteRenderer::draw(sf::RenderWindow& window) const {
    if (sprite) {
        window.draw(*sprite);
    }
}

/**
 * @brief Clears the global texture cache.
 *
 * Removes all cached textures from memory.
 */
void SpriteRenderer::clearCache() {
    textureCache.clear();
}
