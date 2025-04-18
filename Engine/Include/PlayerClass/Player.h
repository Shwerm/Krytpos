/**
 * @file Player.h
 * @brief Represents the player character in the Kryptos Engine.
 *
 * @ingroup PlayerSystem, CombatSystem
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include "../GameObjectSystem/GameObject.h"
#include "../SpriteRenderingSystem/SpriteRenderer.h"
#include "StaminaSystem.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

 /**
  * @class Player
  * @brief Inherits from GameObject and defines player-specific attributes and behaviours.
  *
  * Handles health, stamina, movement, jumping, and attack logic for the player character.
  */
class Player : public GameObject
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs a new Player.
     * @param name Name of the player object.
     * @param position Initial position in world space.
     * @param texturePathRight Texture to use when facing right.
     */
    Player(const std::string& name, const sf::Vector2f& position, const std::string& texturePathRight);

    /**
     * @brief Virtual destructor.
     */
    ~Player() override = default;

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    void handleAttack();
    void takeDamage(float amount);
    void checkDeath();

    void setRespawnPosition(const sf::Vector2f& position);

    // -----------------------------------------------------
    // Getters
    // -----------------------------------------------------

    float getHealth() const;
    float getMaxHealth() const;
    float getAttackSpeed() const;
    float getMovementSpeed() const;
    float getAttackMultiplier() const;
    float getJumpMultiplier() const;

    float getStamina() const;
    float getMaxStamina() const;
    float getStaminaRatio() const;

    // -----------------------------------------------------
    // Setters
    // -----------------------------------------------------

    void setHealth(float value);
    void setMaxHealth(float value);
    void setAttackSpeed(float value);
    void setMovementSpeed(float value);
    void setAttackMultiplier(float value);
    void setJumpMultiplier(float value);

    // -----------------------------------------------------
    // Public Members (temporary)
    // -----------------------------------------------------

    bool previousMousePressed = false; ///< Tracks last frame's mouse state for attack input.

private:
    // -----------------------------------------------------
    // Player Attributes
    // -----------------------------------------------------

    float health;
    float maxHealth;
    float attackSpeed;
    float movementSpeed;
    float attackMultiplier;
    float jumpMultiplier;

    bool isGrounded = false;
    bool isFacingRight = true;

    // -----------------------------------------------------
    // Components & Resources
    // -----------------------------------------------------

    SpriteRenderer spriteRenderer;
    StaminaSystem staminaSystem;

    std::string texturePathRight;
    std::string texturePathLeft;

    // -----------------------------------------------------
    // Respawn Logic
    // -----------------------------------------------------

    sf::Vector2f respawnPosition;
    float fallThresholdY = 430.f;

    // -----------------------------------------------------
    // Damage Logic
    // -----------------------------------------------------

    float damageCooldown = 0.f;
};
