/**
 * @file StaminaBar.cpp
 * @brief Implements the stamina UI bar for displaying player stamina ratio.
 *
 * @ingroup UISystem
 *
 * This UI element displays a fillable blue bar below the health bar that scales based on stamina usage.
 * It tracks a reference to the Player object to reflect real-time gameplay status.
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/UI/StaminaBar.h"
#include "../../Include/PlayerClass/Player.h" // Access to stamina getters

 // -----------------------------------------------------
 // Constructor
 // -----------------------------------------------------

 /**
  * @brief Constructs the stamina bar and positions it on screen.
  * @param playerRef Pointer to the player object to query stamina ratio from.
  * @param screenSize Used to anchor the bar to the bottom-right of the screen.
  */
StaminaBarObject::StaminaBarObject(Player* playerRef, const sf::Vector2f& screenSize)
    : GameObject("StaminaBar", { 0.f, 0.f }, true, sf::degrees(0), 0.f, false),
    backgroundRenderer("StaminaBar_BG"),
    fillRenderer("StaminaBar_Fill"),
    player(playerRef),
    offsetFromBottomRight({ 20.f, 50.f }) // Appears slightly below HealthBar
{
    backgroundRenderer.loadTexture("Assets/GameAssets/Textures/UI/EmptyBar.png");
    fillRenderer.loadTexture("Assets/GameAssets/Textures/UI/BlueBar.png");

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
 * @brief Dynamically updates the width of the stamina fill bar based on current stamina ratio.
 * @param deltaTime Frame time delta (unused).
 */
void StaminaBarObject::update(float deltaTime)
{
    if (!player) return;

    float percentage = player->getStaminaRatio();

    fillRenderer.setTextureRect({
        { 0, 0 },
        { static_cast<int>(200.f * percentage), 28 } // Match HealthBar size
        });
}

// -----------------------------------------------------
// Draw
// -----------------------------------------------------

/**
 * @brief Draws both background and fill bar to the screen.
 * @param window Target SFML render window.
 */
void StaminaBarObject::draw(sf::RenderWindow& window)
{
    backgroundRenderer.draw(window);
    fillRenderer.draw(window);
}
