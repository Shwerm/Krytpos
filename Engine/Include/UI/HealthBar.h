/**
 * @file HealthBar.h
 * @brief UI element that visually represents the player's health.
 *
 * @ingroup UISystem
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include "../../Include/GameObjectSystem/GameObject.h"
#include "../../Include/SpriteRenderingSystem/SpriteRenderer.h"

class Player; // Forward declaration

/**
 * @class HealthBarObject
 * @brief Displays a fill bar in the bottom-right corner representing player health.
 *
 * Automatically scales and positions itself relative to screen size and health values.
 */
class HealthBarObject : public GameObject
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs a health bar UI element.
     * @param playerRef Pointer to the Player object to track.
     * @param screenSize Size of the render screen for relative positioning.
     */
    HealthBarObject(Player* playerRef, const sf::Vector2f& screenSize);

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    SpriteRenderer backgroundRenderer; ///< Background of the health bar.
    SpriteRenderer fillRenderer;       ///< Fill portion of the bar based on current health.

    Player* player; ///< Reference to the player to read health from.
    sf::Vector2f offsetFromBottomRight; ///< UI offset from bottom-right of the screen.
};
