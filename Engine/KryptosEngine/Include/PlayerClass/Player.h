/*
 * Player.h - Kryptos Player Class
 * --------------------------------
 * Defines the Player class, derived from GameObject, with gameplay-specific properties
 * such as health, movement, and attack multipliers.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - GameObject.h: Base class for all game objects.
 *   - SpriteRenderer.h: For rendering the player's sprite.
 */

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
    float health;                   ///< Player's current health.
    float attackSpeed;              ///< Speed of the player's attacks.
    float movementSpeed;            ///< Speed at which the player moves.
    float attackMultiplier;         ///< Multiplier for attack damage.
    float jumpMultiplier;           ///< Multiplier for jump height.
    SpriteRenderer spriteRenderer;  ///< Renders the player's sprite.

public:
    /**
     * @brief Constructs a Player object.
     *
     * Initializes the player with specified parameters and default attributes.
     * @param name The name of the player.
     * @param position The initial position of the player.
     * @param texturePath Path to the texture used for the player's sprite.
     */
    Player(const std::string& name, const sf::Vector2f& position, const std::string& texturePath);

    /**
     * @brief Destructor for the Player class.
     */
    ~Player() override = default;

    /**
     * @brief Updates the player's logic.
     * @param deltaTime Time elapsed since the last frame, used for time-based updates.
     */
    void update(float deltaTime);

    /**
     * @brief Renders the player to the given window.
     * @param window The render window where the player is drawn.
     */
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
