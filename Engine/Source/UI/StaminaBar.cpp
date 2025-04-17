#include "../../Include/UI/StaminaBar.h"
#include "../../Include/PlayerClass/Player.h" // Access to stamina getters

StaminaBarObject::StaminaBarObject(Player* playerRef, const sf::Vector2f& screenSize)
    : GameObject("StaminaBar", { 0.f, 0.f }, true, sf::degrees(0), 0.f, false),
    backgroundRenderer("StaminaBar_BG"),
    fillRenderer("StaminaBar_Fill"),
    player(playerRef),
    offsetFromBottomRight({ 20.f, 10.f }) // Slightly below health bar
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

void StaminaBarObject::update(float deltaTime)
{
    if (!player) return;

    float percentage = player->getStaminaRatio();

    fillRenderer.setTextureRect({
        { 0, 0 },
        { static_cast<int>(200.f * percentage), 28 } // same size as health bar
        });
}

void StaminaBarObject::draw(sf::RenderWindow& window)
{
    backgroundRenderer.draw(window);
    fillRenderer.draw(window);
}
