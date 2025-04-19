/**
 * @file ParallaxBackground.cpp
 * @brief Implementation of the ParallaxBackground class for layered scrolling backgrounds.
 *
 * @ingroup RenderingSystem
 *
 * Manages and renders multiple parallax layers based on camera movement,
 * creating depth perception in a 2D environment using texture layers.
 *
 * Each layer scrolls at a different speed and can be configured individually.
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/EnvironmentGenerator/ParallaxBackground.h"

 // -----------------------------------------------------
 // Constructor
 // -----------------------------------------------------

 /**
  * @brief Constructs the parallax background with all predefined layers.
  * @param windowWidth Width of the camera window for tiling/wrapping layers.
  */
ParallaxBackground::ParallaxBackground(float windowWidth)
{
    // Sky layer (locked in X)
    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-bg.png",
        0.0f, windowWidth, 4.0f, -50.0f, 0.0f, false, true));

    // Background mountain far (slow)
    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-montain-far.png",
        0.25f, windowWidth, 4.0f, 100.0f, -420.0f));

    // Mid-range mountains
    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-mountains.png",
        0.4f, windowWidth, 4.0f, 300.0f, -420.0f));

    // Background trees
    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-trees.png",
        0.6f, windowWidth, 4.0f, 360.0f, -420.0f));

    // Foreground trees
    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-foreground-trees.png",
        0.8f, windowWidth, 4.0f, 360.0f, -420.0f));
}

// -----------------------------------------------------
// Public Methods
// -----------------------------------------------------

/**
 * @brief Updates all parallax layers relative to the camera's position.
 * @param cameraX Horizontal position of the camera in world space.
 * @param cameraView Current camera view for centring and wrapping logic.
 */
void ParallaxBackground::update(float cameraX, const sf::View& cameraView)
{
    for (auto& layer : layers)
    {
        layer->update(cameraX, cameraView);
    }
}

/**
 * @brief Draws all parallax layers in order to the target render surface.
 * @param target Render target (e.g., window or texture).
 */
void ParallaxBackground::draw(sf::RenderTarget& target)
{
    for (auto& layer : layers)
    {
        layer->draw(target);
    }
}
