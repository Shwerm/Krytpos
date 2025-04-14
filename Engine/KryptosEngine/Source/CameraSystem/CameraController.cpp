#include "../../Include/CameraSystem/CameraController.h"

CameraController::CameraController(float width, float height)
{
    m_view.setSize(width, height);
    m_view.setCenter(width / 2.0f, height / 2.0f);
}

void CameraController::Update(const sf::Vector2f& playerPosition)
{
    // Lock the view to the player's X and Y position
    m_view.setCenter(playerPosition);
}

void CameraController::ApplyView(sf::RenderWindow& window) const
{
    window.setView(m_view);
}
