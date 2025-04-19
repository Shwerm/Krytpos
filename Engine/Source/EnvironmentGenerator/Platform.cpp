/**
 * @file Platform.cpp
 * @brief Implementation of the Platform class, used for level structure and terrain.
 *
 * @ingroup EnvironmentSystem
 *
 * Represents static platforms that can be walked on or jumped between.
 * Each platform has its own SpriteRenderer and optional collider.
 * Typically spawned by the EnvironmentGenerator or placed manually.
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/EnvironmentGenerator/Platform.h"

 // -----------------------------------------------------
 // Constructor
 // -----------------------------------------------------

 /**
  * @brief Constructs a platform with a name, world-space position, and texture.
  * @param name Unique identifier for the platform.
  * @param position Position in world space where it should appear.
  * @param texturePath Path to the texture asset for the platform.
  */
Platform::Platform(const std::string& name, const sf::Vector2f& position, const std::string& texturePath)
    : GameObject(name, position, true, sf::degrees(0), 0.0f, false)
{
    renderer = std::make_unique<SpriteRenderer>(name);
    renderer->loadTexture(texturePath);
    renderer->setPosition(position);

    useGravity = false;

    // Assign a simple box collider to the platform
    addCollider({ 32.f, 7.f }, { 0.f, 5.f });
}

// -----------------------------------------------------
// Public Methods
// -----------------------------------------------------

/**
 * @brief Draws the platform sprite and debug collider if enabled.
 * @param window SFML render window to draw to.
 */
void Platform::draw(sf::RenderWindow& window)
{
    if (renderer)
        renderer->draw(window);

    bool showColliders = true;
    if (showColliders && hasCollider())
        getCollider()->drawDebug(window);
}
