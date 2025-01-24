/*
Sprite Renderer source - Kryptos - Sam Camilleri, Mural Studios
All Rights Reserved 2025.
Dependencies: Graphics.hpp, vector, string, GameObject.h
*/
#include "../Include/SpriteRenderingSystem/SpriteRenderer.h"
#include <stdexcept>

// Initialize the static texture cache
std::unordered_map<std::string, std::shared_ptr<sf::Texture>> SpriteRenderer::textureCache;

// Constructor
SpriteRenderer::SpriteRenderer() : sprite(nullptr), texture(nullptr) {}

// Load a texture and set it for the sprite
void SpriteRenderer::loadTexture(const std::string& texturePath) {
    // Check if texture is already in the cache
    auto it = textureCache.find(texturePath);
    if (it != textureCache.end()) {
        texture = it->second;
    }
    else {
        // Load texture and store it in the cache
        auto newTexture = std::make_shared<sf::Texture>();
        if (!newTexture->loadFromFile(texturePath)) {
            throw std::runtime_error("Failed to load texture from: " + texturePath);
        }
        textureCache[texturePath] = newTexture;
        texture = newTexture;
    }

    // Create the sprite using the texture
    sprite = std::make_unique<sf::Sprite>(*texture);
}

// Set the position of the sprite
void SpriteRenderer::setPosition(const sf::Vector2f& position) {
    if (sprite) {
        sprite->setPosition(position);
    }
}

// Get the position of the sprite
sf::Vector2f SpriteRenderer::getPosition() const {
    return sprite ? sprite->getPosition() : sf::Vector2f(0.f, 0.f);
}

// Set the origin of the sprite for transformations
void SpriteRenderer::setOrigin(const sf::Vector2f& origin) {
    if (sprite) {
        sprite->setOrigin(origin);
    }
}

// Set the rotation of the sprite (convert float to sf::Angle)
void SpriteRenderer::setRotation(float angle) {
    if (sprite) {
        sprite->setRotation(sf::degrees(angle)); // Convert degrees to sf::Angle
    }
}

// Get the current rotation of the sprite (convert sf::Angle to float)
float SpriteRenderer::getRotation() const {
    return sprite ? sprite->getRotation().asDegrees() : 0.f;
}

// Set the scale of the sprite
void SpriteRenderer::setScale(const sf::Vector2f& scale) {
    if (sprite) {
        sprite->setScale(scale);
    }
}

// Get the scale of the sprite
sf::Vector2f SpriteRenderer::getScale() const {
    return sprite ? sprite->getScale() : sf::Vector2f(1.f, 1.f);
}

// Render the sprite to the given render window
void SpriteRenderer::draw(sf::RenderWindow& window) const {
    if (sprite) {
        window.draw(*sprite);
    }
}

// Clear the texture cache
void SpriteRenderer::clearCache() {
    textureCache.clear();
}
