#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief Manages the camera view that follows the player.
 */
class CameraController
{
public:
    CameraController(float width, float height);

    /**
     * @brief Updates the camera view to follow the player.
     * @param playerPosition The position of the player.
     */
    void Update(const sf::Vector2f& playerPosition);

    /**
     * @brief Applies the current view to the given render window.
     * @param window The render window to apply the view to.
     */
    void ApplyView(sf::RenderWindow& window) const;

private:
    sf::View m_view;
};
