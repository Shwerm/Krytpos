#ifndef PLAYER_H
#define PLAYER_H

#include "../GameObjectSystem/GameObject.h"
#include "../SpriteRenderingSystem/SpriteRenderer.h"
#include "StaminaSystem.h" 
#include <iostream>

/**
 * @class Player
 * @brief Represents the player character in the Kryptos game engine.
 *
 * Inherits from GameObject and adds player-specific attributes such as
 * health, movement speed, attack speed, and multipliers for attacking and jumping.
 */
class Player : public GameObject {
private:
    float health;
    float maxHealth;
    float attackSpeed;
    float movementSpeed;
    float attackMultiplier;
    float jumpMultiplier;
    bool isGrounded = false;
    bool isFacingRight = true;
    SpriteRenderer spriteRenderer;

    sf::Vector2f respawnPosition;
    float fallThresholdY = 1000.f;

    std::string texturePathRight;
    std::string texturePathLeft;

    StaminaSystem staminaSystem; // Added stamina system member

public:
    Player(const std::string& name, const sf::Vector2f& position, const std::string& texturePathRight);
    ~Player() override = default;

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    void setRespawnPosition(const sf::Vector2f& position);

    float getHealth() const;
    void setHealth(float value);

    float getMaxHealth() const;
    void setMaxHealth(float value);

    float getAttackSpeed() const;
    void setAttackSpeed(float value);

    float getMovementSpeed() const;
    void setMovementSpeed(float value);

    float getAttackMultiplier() const;
    void setAttackMultiplier(float value);

    float getJumpMultiplier() const;
    void setJumpMultiplier(float value);

    // Stamina accessors for future UI or gameplay
    float getStamina() const;
    float getMaxStamina() const;
    float getStaminaRatio() const;

    void handleAttack();

};

#endif // PLAYER_H
