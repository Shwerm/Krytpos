#include "../../Include/UI/HealthBar.h"
#include "../../Include/PlayerClass/Player.h" // Ensure Player includes getHealth(), getMaxHealth()

HealthBarObject::HealthBarObject(Player* playerRef, const sf::Vector2f& screenSize)
    : GameObject("HealthBar", { 0.f, 0.f }, true, sf::degrees(0), 0.f, false),
    backgroundRenderer("HealthBar_BG"),
    fillRenderer("HealthBar_Fill"),
    player(playerRef),
    offsetFromBottomRight({ 220.f, 40.f }) // adjust for size of bar
{
    // Load both textures
    backgroundRenderer.loadTexture("Assets/EngineAssets/Textures/UI/EmptyBar.png");
    fillRenderer.loadTexture("Assets/EngineAssets/Textures/UI/RedBar.png");

    // Set positions (bottom-right anchored)
    sf::Vector2f basePos = {
        screenSize.x - offsetFromBottomRight.x,
        screenSize.y - offsetFromBottomRight.y
    };

    backgroundRenderer.setPosition(basePos);
    fillRenderer.setPosition(basePos);
}

void HealthBarObject::update(float deltaTime)
{
    if (!player) return;

    float current = player->getHealth();
    float max = player->getMaxHealth();
    float percentage = (max > 0.f) ? (current / max) : 0.f;

    const auto& tex = fillRenderer.getScale(); // or .getSize() if available
    fillRenderer.setTextureRect({
        { 0, 0 },
        { static_cast<int>(200.f * percentage), 28 } // assuming bar is 200px wide
        });
}

void HealthBarObject::draw(sf::RenderWindow& window)
{
    backgroundRenderer.draw(window);
    fillRenderer.draw(window);
}
