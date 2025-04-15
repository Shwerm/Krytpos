#ifndef PLAYER_H
#define PLAYER_H

#include "../GameObjectSystem/GameObject.h"
#include "../SpriteRenderingSystem/SpriteRenderer.h"

/**
 * @class Player
 * @brief Represents the player character in the Kryptos game engine.
 *
 * The Player class extends GameObject and includes player-specific attributes such as health,
 * movement speed, attack speed, and multipliers for attacks and jumping.
 */
class Player : public GameObject {
private:
    float health;
    float attackSpeed;
    float movementSpeed;
    float attackMultiplier;
    float jumpMultiplier;
    bool isGrounded = false; ///< Whether the player is currently grounded
    SpriteRenderer spriteRenderer;

public:
    Player(const std::string& name, const sf::Vector2f& position, const std::string& texturePath);
    ~Player() override = default;

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    // Getters and setters for health
    float getHealth() const;
    void setHealth(float value);

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
