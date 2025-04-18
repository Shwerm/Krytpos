/**
 * @file CameraController.h
 * @brief 2D Camera View Controller for the Rendering System.
 *
 * @ingroup RenderingSystem
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include <SFML/Graphics.hpp>

 /**
  * @class CameraController
  * @brief Manages a dynamic 2D camera that follows a target position (typically the player).
  *
  * Updates and applies a viewport view based on the target’s position, maintaining a centred camera.
  */
class CameraController
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs the camera controller with a specified view size.
     * @param width Width of the camera view.
     * @param height Height of the camera view.
     */
    CameraController(float width, float height);

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    /**
     * @brief Updates the camera's view to follow the given target position.
     * @param playerPosition Current position of the target in world space.
     */
    void Update(const sf::Vector2f& playerPosition);

    /**
     * @brief Applies the internal view to the specified render window.
     * @param window The target SFML render window.
     */
    void ApplyView(sf::RenderWindow& window) const;

    // -----------------------------------------------------
    // Getter
    // -----------------------------------------------------

    /**
     * @brief Returns the internal SFML view object.
     * @return A constant reference to the sf::View.
     */
    const sf::View& GetView() const { return m_view; }

private:
    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    sf::View m_view; ///< SFML view instance representing the camera's viewport.
};
