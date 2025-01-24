/*
Sprite Renderer header - Kryptos - Sam Camilleri, Mural Studios
All Rights Reserved 2025.
Dependencies: Graphics.hpp, string, unordered_map, memory
*/

#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <memory>

class SpriteRenderer {
private:
    std::unique_ptr<sf::Sprite> sprite;             // Unique pointer to the sprite
    std::shared_ptr<sf::Texture> texture;           // Shared texture for efficient memory usage
    static std::unordered_map<std::string,          // Cache for loaded textures
        std::shared_ptr<sf::Texture>> textureCache;

public:
    // Constructor
    SpriteRenderer();

    // Destructor
    ~SpriteRenderer() = default;

    // Load a texture and set it for the sprite
    void loadTexture(const std::string& texturePath);

    // Set the position of the sprite
    void setPosition(const sf::Vector2f& position);

    // Get the position of the sprite
    sf::Vector2f getPosition() const;

    // Set the origin of the sprite for transformations
    void setOrigin(const sf::Vector2f& origin);

    // Set the rotation of the sprite
    void setRotation(float angle);

    // Get the current rotation of the sprite
    float getRotation() const;

    // Set the scale of the sprite
    void setScale(const sf::Vector2f& scale);

    // Get the scale of the sprite
    sf::Vector2f getScale() const;

    // Render the sprite to the given render window
    void draw(sf::RenderWindow& window) const;

    // Static method to clear the texture cache
    static void clearCache();
};

#endif // SPRITERENDERER_H
