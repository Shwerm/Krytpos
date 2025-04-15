// CameraController.cpp

#include "../../Include/CameraSystem/CameraController.h"

/**
 * @brief Constructor that initialises the camera view with the specified size and centres it.
 * @param width Width of the view.
 * @param height Height of the view.
 */
CameraController::CameraController(float width, float height)
{
    // Set the view size to the given width and height
    m_view.setSize(sf::Vector2f(width, height));

    // Centre the view initially at the middle of the screen
    m_view.setCenter(sf::Vector2f(width / 2.0f, height / 2.0f));
}

/**
 * @brief Updates the camera's centre to follow the given player position.
 * @param playerPosition The player's world position to centre the view on.
 */
void CameraController::Update(const sf::Vector2f& playerPosition)
{
    m_view.setCenter(playerPosition);
}

/**
 * @brief Applies the internal camera view to the specified render window.
 * @param window The SFML render window to apply the current view to.
 */
void CameraController::ApplyView(sf::RenderWindow& window) const
{
    window.setView(m_view);
}
