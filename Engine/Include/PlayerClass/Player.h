#ifndef PLAYER_H
#define PLAYER_H

#include "../GameObjectSystem/GameObject.h"
#include "../SpriteRenderingSystem/SpriteRenderer.h"

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
    bool isGrounded = false; ///< Tracks if the player is currently grounded
    SpriteRenderer spriteRenderer;

    sf::Vector2f respawnPosition;  ///< The position to respawn to
    float fallThresholdY = 1000.f; ///< Y value below which the player respawns

public:
    Player(
        const std::string& name,
        const sf::Vector2f& position,
        const std::string& texturePath);
    ~Player() override = default;

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    void setRespawnPosition(const sf::Vector2f& position);

    // Getters and setters for health
    float getHealth() const;
    void setHealth(float value);

    float getMaxHealth() const;
    void setMaxHealth(float value);


    // Getters and setters for attack speed
    float getAttackSpeed() const;
    void setAttackSpeed(float value);

    // Getters and setters for movement speed
    float getMovementSpeed() const;
    void setMovementSpeed(float value);

    // Getters and setters for attack multiplier
    float getAttackMultiplier() const;
    void setAttackMultiplier(float value);

    // Getters and setters for jump multiplier
    float getJumpMultiplier() const;
    void setJumpMultiplier(float value);
};

#endif // PLAYER_H
