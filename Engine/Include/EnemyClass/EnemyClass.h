// EnemyClass.h - Kryptos Enemy Game Object Class
#pragma once

#include "../GameObjectSystem/GameObject.h"
#include "../SpriteRenderingSystem/SpriteRenderer.h"

/**
 * @class EnemyClass
 * @brief Represents an enemy entity inheriting from GameObject.
 *
 * Handles unique enemy attributes such as health, movement speed,
 * attack multiplier, and visual rendering using a sprite sheet.
 */
class EnemyClass : public GameObject {
private:
    float health;
    float movementSpeed;
    float attackMultiplier;
    SpriteRenderer spriteRenderer;
    bool movingLeft = true;
    bool isGrounded = false;

    float flipCooldown = 0.f;
    const float flipCooldownDuration = 0.4f; // seconds



public:
    EnemyClass(
        const std::string& name,
        const sf::Vector2f& position,
        const std::string& texturePath);

    ~EnemyClass() override = default;

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    // Getters
    float getHealth() const;
    float getMovementSpeed() const;
    float getAttackMultiplier() const;

    // Setters
    void setHealth(float value);
    void setMovementSpeed(float value);
    void setAttackMultiplier(float value);

    void fixedUpdate(float fixedDeltaTime) override;
};
