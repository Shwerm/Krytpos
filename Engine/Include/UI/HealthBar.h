#pragma once

#include "../../Include/GameObjectSystem/GameObject.h"
#include "../../Include/SpriteRenderingSystem/SpriteRenderer.h"

class Player; // Forward declare Player

class HealthBarObject : public GameObject {
public:
    HealthBarObject(Player* playerRef, const sf::Vector2f& screenSize);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    SpriteRenderer backgroundRenderer;
    SpriteRenderer fillRenderer;

    Player* player; // Reference to track health
    sf::Vector2f offsetFromBottomRight;
};
