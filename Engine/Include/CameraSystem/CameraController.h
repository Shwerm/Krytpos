// CameraController.h

#pragma once

#include <SFML/Graphics.hpp>

/**
 * @class CameraController
 * @brief Handles the 2D camera system by controlling and updating the view to follow a target (e.g. player).
 *
 * This class is responsible for maintaining a view that follows a player or entity in the scene,
 * and applying the view to the render window before drawing.
 */
class CameraController
{
public:
    /**
     * @brief Constructs a camera controller with a specified view size.
     * @param width Width of the camera view.
     * @param height Height of the camera view.
     */
    CameraController(float width, float height);

    /**
     * @brief Updates the camera view to follow the player's position.
     * @param playerPosition The current world position of the player.
     */
    void Update(const sf::Vector2f& playerPosition);

    /**
     * @brief Applies the current camera view to the given SFML render window.
     * @param window The render window to which the view will be set.
     */
    void ApplyView(sf::RenderWindow& window) const;

    /**
     * @brief Returns the current internal SFML view.
     */
    const sf::View& GetView() const { return m_view; }

private:
    sf::View m_view; ///< The internal SFML view object used to control the camera.
};
