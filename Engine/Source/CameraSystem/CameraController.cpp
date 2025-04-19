/**
 * @file CameraController.cpp
 * @brief Implementation of the CameraController class used to follow a target in 2D space.
 *
 * @ingroup RenderingSystem
 *
 * Updates an SFML view to follow the player or any tracked target.
 * Applies the current view to the render window before drawing.
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/CameraSystem/CameraController.h"

 // -----------------------------------------------------
 // Constructor
 // -----------------------------------------------------

 /**
  * @brief Constructs the camera controller and initialises the SFML view.
  * @param width Width of the camera view.
  * @param height Height of the camera view.
  */
CameraController::CameraController(float width, float height)
{
    // Set the logical size of the view to the given dimensions
    m_view.setSize(sf::Vector2f(width, height));

    // Centre the view initially on the screen midpoint
    m_view.setCenter(sf::Vector2f(width / 2.0f, height / 2.0f));
}

// -----------------------------------------------------
// Public Methods
// -----------------------------------------------------

/**
 * @brief Updates the camera's view to follow the player.
 * @param playerPosition The world-space position to centre the view on.
 */
void CameraController::Update(const sf::Vector2f& playerPosition)
{
    // Reposition the camera view to track the player
    m_view.setCenter(playerPosition);
}

/**
 * @brief Applies the current view to the given SFML render window.
 * @param window The render window to apply the view to.
 */
void CameraController::ApplyView(sf::RenderWindow& window) const
{
    window.setView(m_view);
}
