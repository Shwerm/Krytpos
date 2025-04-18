/**
 * @file EnemyClass.h
 * @brief Enemy entity class derived from the base GameObject.
 *
 * @ingroup EnemySystem
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include "../GameObjectSystem/GameObject.h"
#include "../SpriteRenderingSystem/SpriteRenderer.h"
#include <SFML/Graphics.hpp>

 /**
  * @class EnemyClass
  * @brief Represents an enemy object with basic movement, health, and attack properties.
  *
  * Provides rendering, knockback, and AI-like movement features for a platformer enemy.
  */
class EnemyClass : public GameObject
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs an enemy with a name, position, and texture.
     * @param name Unique identifier.
     * @param position Initial spawn position.
     * @param texturePath Path to the sprite texture.
     */
    EnemyClass(const std::string& name, const sf::Vector2f& position, const std::string& texturePath);

    /**
     * @brief Default destructor.
     */
    ~EnemyClass() override = default;

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    /**
     * @brief Updates the enemy every frame (non-physics).
     * @param deltaTime Elapsed time since last frame.
     */
    void update(float deltaTime) override;

    /**
     * @brief Draws the enemy sprite.
     * @param window Target SFML render window.
     */
    void draw(sf::RenderWindow& window) override;

    /**
     * @brief Updates enemy physics at fixed intervals.
     * @param fixedDeltaTime Fixed time step.
     */
    void fixedUpdate(float fixedDeltaTime) override;

    /**
     * @brief Applies a force to the enemy for knockback.
     * @param force Knockback vector to apply.
     */
    void applyKnockback(const sf::Vector2f& force);

    // -----------------------------------------------------
    // Getters
    // -----------------------------------------------------

    /**
     * @brief Returns current health value.
     * @return Health as float.
     */
    float getHealth() const;

    /**
     * @brief Returns current movement speed.
     * @return Speed as float.
     */
    float getMovementSpeed() const;

    /**
     * @brief Returns attack damage multiplier.
     * @return Multiplier as float.
     */
    float getAttackMultiplier() const;

    // -----------------------------------------------------
    // Setters
    // -----------------------------------------------------

    /**
     * @brief Sets the enemy's health value.
     * @param value New health amount.
     */
    void setHealth(float value);

    /**
     * @brief Sets the movement speed.
     * @param value New speed value.
     */
    void setMovementSpeed(float value);

    /**
     * @brief Sets the attack multiplier.
     * @param value New attack multiplier.
     */
    void setAttackMultiplier(float value);

private:
    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    float health;              ///< Current health of the enemy.
    float movementSpeed;       ///< Movement speed factor.
    float attackMultiplier;    ///< Multiplier applied to attacks.
    SpriteRenderer spriteRenderer; ///< Sprite renderer used for enemy visuals.

    bool movingLeft = true;    ///< Indicates movement direction.
    bool isGrounded = false;   ///< Whether the enemy is grounded.

    float flipCooldown = 0.f;                  ///< Cooldown timer for direction flipping.
    const float flipCooldownDuration = 0.4f;   ///< Duration to wait between flips.
};
