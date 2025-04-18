/**
 * @file Platform.h
 * @brief Represents a static or generated platform in the game environment.
 *
 * @ingroup EnvironmentSystem
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include "../GameObjectSystem/GameObject.h"
#include "../SpriteRenderingSystem/SpriteRenderer.h"
#include <SFML/Graphics.hpp>
#include <memory>

 /**
  * @class Platform
  * @brief Defines a game object that visually represents a static platform.
  *
  * Used for procedural generation or hand-placed level elements.
  */
class Platform : public GameObject
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs a new Platform object.
     * @param name Unique identifier for the platform.
     * @param position Initial position in world space.
     * @param texturePath Path to the texture asset for rendering.
     */
    Platform(const std::string& name, const sf::Vector2f& position, const std::string& texturePath);

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    /**
     * @brief Draws the platform sprite using its renderer.
     * @param window Target SFML render window.
     */
    void draw(sf::RenderWindow& window) override;

private:
    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    std::unique_ptr<SpriteRenderer> renderer; ///< Sprite renderer used to draw the platform.
};
