/**
 * @file AttackHitbox.h
 * @brief Represents a temporary hitbox used for melee attack collision detection.
 *
 * @ingroup CombatSystem
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include "../GameObjectSystem/GameObject.h"
#include "../2DCollider/Collider2D.h"
#include <SFML/Graphics.hpp>

 /**
  * @class AttackHitbox
  * @brief Temporary GameObject that detects and applies damage/knockback to enemies.
  *
  * Self-destructs after a short lifetime to prevent persistent collisions.
  */
class AttackHitbox : public GameObject
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs a new AttackHitbox instance.
     * @param name Identifier name.
     * @param position Starting world-space position.
     * @param direction Normalised direction vector for hit direction.
     */
    AttackHitbox(const std::string& name, const sf::Vector2f& position, const sf::Vector2f& direction);

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    /**
     * @brief Updates hitbox logic and self-destruction countdown.
     * @param deltaTime Elapsed time since last frame.
     */
    void update(float deltaTime) override;

    /**
     * @brief Renders a visual representation of the hitbox (optional for debug).
     * @param window SFML render window.
     */
    void draw(sf::RenderWindow& window) override;

private:
    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    float lifetime = 0.2f; ///< Duration in seconds before this hitbox is destroyed.
    sf::Vector2f direction; ///< Direction the hitbox is facing/knocking back.
};
