#pragma once

#include "../GameObjectSystem/GameObject.h"
#include "../2DCollider/Collider2D.h"

/**
 * @class AttackHitbox
 * @brief Temporary hitbox created by the player to deal knockback damage to enemies.
 */
class AttackHitbox : public GameObject {
private:
    float lifetime = 0.2f; // Seconds until this hitbox destroys itself
    sf::Vector2f direction;

public:
    AttackHitbox(const std::string& name, const sf::Vector2f& position, const sf::Vector2f& direction);
    void update(float deltaTime) override;
};
