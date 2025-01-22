#ifndef PLAYER_H
#define PLAYER_H

#include "../GameObjectSystem/GameObject.h"
#include "../SpriteRenderingSystem/SpriteRenderer.h"

class Player : public GameObject {
private:
    float health;                   // Player's health
    float attackSpeed;              // Speed of attacks
    float movementSpeed;            // Speed of movement
    float attackMultiplier;         // Damage multiplier for attacks
    float jumpMultiplier;           // Jump height multiplier
    SpriteRenderer spriteRenderer;  // Sprite renderer for the player

public:
    // Constructor
    Player(const std::string& name, const sf::Vector2f& position, const std::string& texturePath);

    // Destructor
    ~Player() override = default;

    // Update the player's logic
    void update(float deltaTime) override;

    // Render the player
    void draw(sf::RenderWindow& window) override;

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
