// EnemyClass.h - Kryptos Enemy Game Object Class
#pragma once

#include "../GameObjectSystem/GameObject.h"
#include "../SpriteRenderingSystem/SpriteRenderer.h"

class EnemyClass : public GameObject {
private:
    float health;
    float movementSpeed;
    float attackMultiplier;
    sf::Sprite spriteRenderer;

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
    const sf::Sprite& getSpriteRenderer() const;

    // Setters
    void setHealth(float value);
    void setMovementSpeed(float value);
    void setAttackMultiplier(float value);
};
