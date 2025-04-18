/**
 * @file StaminaBar.h
 * @brief UI element that visually represents the player's stamina.
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
 * @class StaminaBarObject
 * @brief Displays a fill bar in the bottom-right corner representing player stamina.
 *
 * Dynamically adjusts width based on player's current stamina ratio.
 */
class StaminaBarObject : public GameObject
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs a stamina bar UI element.
     * @param playerRef Pointer to the Player object to track.
     * @param screenSize Size of the screen to determine UI position.
     */
    StaminaBarObject(Player* playerRef, const sf::Vector2f& screenSize);

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    SpriteRenderer backgroundRenderer; ///< Static background bar sprite.
    SpriteRenderer fillRenderer;       ///< Foreground bar that scales with stamina.

    Player* player; ///< Reference to player to access stamina values.
    sf::Vector2f offsetFromBottomRight; ///< Offset from screen corner for positioning.
};
