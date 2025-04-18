/**
 * @file ParallaxLayer.h
 * @brief Represents a single scrollable layer in a parallax background.
 *
 * @ingroup ParallaxRenderingSystem
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

 /**
  * @class ParallaxLayer
  * @brief Handles a texture layer that scrolls independently from the camera for a parallax effect.
  *
  * Two sprites are used to tile horizontally and wrap seamlessly during movement.
  */
class ParallaxLayer
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs a parallax layer with rendering and scroll parameters.
     * @param texturePath Path to the layer's texture file.
     * @param scrollSpeed Speed at which this layer scrolls relative to camera movement.
     * @param windowWidth Width of the render window used for wrap logic.
     * @param scale Scaling factor for the sprite.
     * @param yOffset Vertical offset in world space.
     * @param xOffset Optional horizontal offset.
     * @param repeat Whether the layer should repeat horizontally.
     * @param lockX If true, the layer's X position is locked and does not scroll.
     */
    ParallaxLayer(const std::string& texturePath,
        float scrollSpeed,
        float windowWidth,
        float scale,
        float yOffset,
        float xOffset = 0.0f,
        bool repeat = true,
        bool lockX = false);

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    /**
     * @brief Updates the horizontal position of the layer based on the camera.
     * @param cameraX X position of the camera.
     * @param cameraView The current camera view for size reference.
     */
    void update(float cameraX, const sf::View& cameraView);

    /**
     * @brief Draws the parallax layer to the given render target.
     * @param target SFML render surface.
     */
    void draw(sf::RenderTarget& target);

private:
    // -----------------------------------------------------
    // Private Methods
    // -----------------------------------------------------

    /**
     * @brief Wraps the sprite positions to maintain seamless tiling as the camera moves.
     * @param cameraX Current X coordinate of the camera.
     * @param viewWidth Width of the camera's view area.
     */
    void wrapSprites(float cameraX, float viewWidth);

    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    sf::Texture texture;                        ///< Texture used for the parallax layer.
    std::unique_ptr<sf::Sprite> sprite1;        ///< First sprite instance for tiling.
    std::unique_ptr<sf::Sprite> sprite2;        ///< Second sprite instance for tiling.

    float speed;                                ///< Scroll speed multiplier.
    float width;                                ///< Width of one full tile (used for wrapping).
    float scale;                                ///< Sprite scale factor.
    float yOffset;                              ///< Vertical offset from camera baseline.
    float xOffset;                              ///< Initial horizontal offset.
    bool repeatEnabled;                         ///< If true, enables horizontal repeating.
    bool lockX;                                 ///< If true, disables horizontal scrolling.
};
