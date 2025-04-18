/**
 * @file SpriteRenderer.h
 * @brief Manages loading, rendering, and transformation of 2D sprites.
 *
 * @ingroup RenderingSystem
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <memory>

 /**
  * @class SpriteRenderer
  * @brief Handles loading and rendering of sprite textures with transformation controls.
  *
  * Includes a static texture cache to prevent redundant file loading.
  */
class SpriteRenderer
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs a SpriteRenderer associated with an object name.
     * @param name Name used for cache and texture context.
     */
    explicit SpriteRenderer(const std::string& name);

    ~SpriteRenderer() = default;

    // -----------------------------------------------------
    // Texture Management
    // -----------------------------------------------------

    /**
     * @brief Loads and assigns a texture to the sprite.
     * @param texturePath Path to the texture image.
     */
    void loadTexture(const std::string& texturePath);

    /**
     * @brief Sets the texture sub-rectangle for sprite-sheet rendering.
     * @param rect Texture rectangle in pixels.
     */
    void setTextureRect(const sf::IntRect& rect);

    /**
     * @brief Resets the texture rectangle to the full image.
     */
    void resetTextureRect();

    /**
     * @brief Clears the global texture cache.
     */
    static void clearCache();

    // -----------------------------------------------------
    // Transform Accessors
    // -----------------------------------------------------

    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;

    void setOrigin(const sf::Vector2f& origin);
    void setRotation(float angle);
    float getRotation() const;

    void setScale(const sf::Vector2f& scale);
    sf::Vector2f getScale() const;

    // -----------------------------------------------------
    // Rendering
    // -----------------------------------------------------

    /**
     * @brief Renders the sprite to a given window.
     * @param window Target SFML render window.
     */
    void draw(sf::RenderWindow& window) const;

private:
    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    std::unique_ptr<sf::Sprite> sprite; ///< The sprite instance to render.
    std::shared_ptr<sf::Texture> texture; ///< Pointer to the sprite's texture.
    std::string objectName; ///< Object context for this renderer.

    static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textureCache; ///< Global cache of loaded textures.
};
