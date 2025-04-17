#pragma once

#include "../../Include/GameObjectSystem/GameObject.h"
#include "../../Include/SpriteRenderingSystem/SpriteRenderer.h"

class Player; // Forward declaration

class StaminaBarObject : public GameObject {
public:
    StaminaBarObject(Player* playerRef, const sf::Vector2f& screenSize);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    SpriteRenderer backgroundRenderer;
    SpriteRenderer fillRenderer;

    Player* player; // Pointer to player to access stamina
    sf::Vector2f offsetFromBottomRight;
};
