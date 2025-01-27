/*
 * SpriteRenderer.h - Kryptos Sprite Rendering System
 * --------------------------------------------------
 * Defines the SpriteRenderer class for rendering sprites in the Kryptos engine.
 * Includes functionality for texture management, transformations, and rendering.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - SFML/Graphics.hpp: For sprite and texture handling.
 *   - string: For texture path management.
 *   - unordered_map: For caching textures.
 *   - memory: For smart pointers.
 */

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
    static std::unordered_map<std::string,          ///< Cache for loaded textures.
        std::shared_ptr<sf::Texture>> textureCache;

public:
    /**
     * @brief Constructs a SpriteRenderer object.
     * Initializes the sprite and texture pointers to nullptr.
     */
    SpriteRenderer();

    /**
     * @brief Destructor for the SpriteRenderer class.
     */
    ~SpriteRenderer() = default;

    /**
     * @brief Loads a texture from a file and sets it for the sprite.
     *
     * Caches the texture for efficient reuse. Throws an exception if the texture cannot be loaded.
     * @param texturePath The file path of the texture to load.
     */
    void loadTexture(const std::string& texturePath);

    /**
     * @brief Sets the position of the sprite in the game world.
     * @param position The new position of the sprite.
     */
    void setPosition(const sf::Vector2f& position);

    /**
     * @brief Gets the current position of the sprite.
     * @return The position of the sprite as a vector.
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Sets the origin of the sprite for transformations.
     * @param origin The new origin of the sprite.
     */
    void setOrigin(const sf::Vector2f& origin);

    /**
     * @brief Sets the rotation of the sprite.
     * @param angle The rotation angle in degrees.
     */
    void setRotation(float angle);

    /**
     * @brief Gets the current rotation of the sprite.
     * @return The rotation angle in degrees.
     */
    float getRotation() const;

    /**
     * @brief Sets the scale of the sprite.
     * @param scale The new scale of the sprite as a vector.
     */
    void setScale(const sf::Vector2f& scale);

    /**
     * @brief Gets the current scale of the sprite.
     * @return The scale of the sprite as a vector.
     */
    sf::Vector2f getScale() const;

    /**
     * @brief Renders the sprite to the specified render window.
     * @param window The render window where the sprite will be drawn.
     */
    void draw(sf::RenderWindow& window) const;

    /**
     * @brief Clears the global texture cache.
     *
     * This function removes all cached textures from memory.
     */
    static void clearCache();
};

#endif // SPRITERENDERER_H
