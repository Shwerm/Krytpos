/**
 * @file HealthBar.cpp
 * @brief Implements a UI element that visually tracks and displays player health.
 *
 * @ingroup UISystem
 *
 * Consists of a background bar and a fill bar that dynamically scales based on health percentage.
 * Tracks a referenced Player object and updates its visual width accordingly each frame.
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/UI/HealthBar.h"
#include "../../Include/PlayerClass/Player.h" // Ensure Player includes getHealth(), getMaxHealth()

 // -----------------------------------------------------
 // Constructor
 // -----------------------------------------------------

 /**
  * @brief Constructs the HealthBar UI object and positions it relative to the screen.
  * @param playerRef Pointer to the player to track health from.
  * @param screenSize Used to anchor the bar to the bottom-right corner of the screen.
  */
HealthBarObject::HealthBarObject(Player* playerRef, const sf::Vector2f& screenSize)
    : GameObject("HealthBar", { 0.f, 0.f }, true, sf::degrees(0), 0.f, false),
    backgroundRenderer("HealthBar_BG"),
    fillRenderer("HealthBar_Fill"),
    player(playerRef),
    offsetFromBottomRight({ 20.f, 80.f }) // adjust for bar size and screen spacing
{
    // Load background and fill bar textures
    backgroundRenderer.loadTexture("Assets/GameAssets/Textures/UI/EmptyBar.png");
    fillRenderer.loadTexture("Assets/GameAssets/Textures/UI/RedBar.png");

    // Position bar relative to bottom-right corner
    sf::Vector2f basePos = {
        offsetFromBottomRight.x,
        screenSize.y - offsetFromBottomRight.y
    };

    backgroundRenderer.setPosition(basePos);
    fillRenderer.setPosition(basePos);
}

// -----------------------------------------------------
// Update
// -----------------------------------------------------

/**
 * @brief Updates the fill bar width based on player's current health percentage.
 * @param deltaTime Time since last frame (unused).
 */
void HealthBarObject::update(float deltaTime)
{
    if (!player) return;

    float current = player->getHealth();
    float max = player->getMaxHealth();
    float percentage = (max > 0.f) ? (current / max) : 0.f;

    // Update fill width (assumes bar is 200px wide, 28px tall)
    fillRenderer.setTextureRect({
        { 0, 0 },
        { static_cast<int>(200.f * percentage), 28 }
        });
}

// -----------------------------------------------------
// Draw
// -----------------------------------------------------

/**
 * @brief Draws the health bar background and fill to the render window.
 * @param window Target SFML render window.
 */
void HealthBarObject::draw(sf::RenderWindow& window)
{
    backgroundRenderer.draw(window);
    fillRenderer.draw(window);
}
