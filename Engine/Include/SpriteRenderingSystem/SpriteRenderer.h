#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <memory>

/**
 * @class SpriteRenderer
 * @brief Handles the rendering of 2D sprites and texture management.
 *
 * The SpriteRenderer class simplifies the process of loading, managing, and
 * rendering sprites. It includes support for texture caching to optimize performance.
 */
class SpriteRenderer {
private:
    std::unique_ptr<sf::Sprite> sprite;             ///< Unique pointer to the sprite instance.
    std::shared_ptr<sf::Texture> texture;           ///< Shared pointer to the sprite's texture.
    std::string objectName;
    static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textureCache;

public:
    explicit SpriteRenderer(const std::string& name);
    ~SpriteRenderer() = default;

    void loadTexture(const std::string& texturePath);
    void setTextureRect(const sf::IntRect& rect);
    void resetTextureRect();

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

    void setOrigin(const sf::Vector2f& origin);
    void setRotation(float angle);
    float getRotation() const;

    void setScale(const sf::Vector2f& scale);
    sf::Vector2f getScale() const;

    void draw(sf::RenderWindow& window) const;

    static void clearCache();
};

#endif // SPRITERENDERER_H
