#include "../../Include/CameraSystem/CameraController.h"


CameraController::CameraController(float width, float height)
{
    m_view.setSize(sf::Vector2f(width, height));
    m_view.setCenter(sf::Vector2f(width / 2.0f, height / 2.0f));
}

void CameraController::Update(const sf::Vector2f& playerPosition)
{
    m_view.setCenter(playerPosition);
}

void CameraController::ApplyView(sf::RenderWindow& window) const
{
    window.setView(m_view);
}

