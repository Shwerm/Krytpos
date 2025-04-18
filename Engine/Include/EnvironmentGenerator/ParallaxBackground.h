/**
 * @file ParallaxBackground.h
 * @brief Manages a layered parallax scrolling background system.
 *
 * @ingroup ParallaxRenderingSystem
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include <vector>
#include <memory>
#include "ParallaxLayer.h"
#include <SFML/Graphics.hpp>

 /**
  * @class ParallaxBackground
  * @brief Coordinates multiple parallax layers to simulate background depth during camera movement.
  *
  * Responsible for updating and drawing each layer in the correct rendering order.
  */
class ParallaxBackground
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs the background manager and sets the reference width.
     * @param windowWidth The visible window width used to tile and position layers.
     */
    ParallaxBackground(float windowWidth);

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    /**
     * @brief Updates all parallax layers based on camera X movement and view.
     * @param cameraX The camera's X position.
     * @param cameraView The active SFML camera view.
     */
    void update(float cameraX, const sf::View& cameraView);

    /**
     * @brief Draws all parallax layers to the target render surface.
     * @param target The SFML render target (window or texture).
     */
    void draw(sf::RenderTarget& target);

private:
    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    std::vector<std::unique_ptr<ParallaxLayer>> layers; ///< Ordered list of parallax layers.
};
