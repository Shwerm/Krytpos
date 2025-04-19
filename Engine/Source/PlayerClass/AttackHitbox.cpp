/**
 * @file AttackHitbox.cpp
 * @brief Handles temporary melee hitbox logic for knockback collisions.
 *
 * @ingroup CombatSystem
 *
 * This GameObject checks for enemy collisions, applies knockback, and self-destructs after a short lifetime.
 * Used by Player attacks. Hitbox is visualised for debugging purposes.
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/PlayerClass/AttackHitbox.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"
#include "../../Include/EnemyClass/EnemyClass.h"
#include <iostream>

 // -----------------------------------------------------
 // Constructor
 // -----------------------------------------------------

 /**
  * @brief Constructs an AttackHitbox object.
  * @param name Identifier used for GameObject management and logging.
  * @param position World-space spawn position of the hitbox.
  * @param direction Direction of the attack (used for knockback).
  */
AttackHitbox::AttackHitbox(const std::string& name, const sf::Vector2f& position, const sf::Vector2f& direction)
    : GameObject(name, position, true, sf::degrees(0), 0.f, false),
    direction(direction)
{
    // Create a centered square collider (32x32)
    addCollider({ 32.f, 32.f }, { -16.f, -16.f });
    getCollider()->setPosition(position);
}

// -----------------------------------------------------
// Update
// -----------------------------------------------------

/**
 * @brief Updates the hitbox each frame. Checks lifetime and collision with enemies.
 * @param deltaTime Elapsed time since last frame.
 */
void AttackHitbox::update(float deltaTime)
{
    // Reduce remaining lifetime
    lifetime -= deltaTime;

    // If expired, remove from world
    if (lifetime <= 0.f)
    {
        GameObjectManager::getInstance().unregisterObject(this);
        delete this;
        return;
    }

    // Check collisions against all active GameObjects
    for (auto* obj : GameObjectManager::getInstance().getGameObjects())
    {
        if (obj == this || !obj->hasCollider()) continue;

        // Check for collision with EnemyClass instances
        auto* enemy = dynamic_cast<EnemyClass*>(obj);
        if (enemy && Collider2D::intersects(*getCollider(), *enemy->getCollider()))
        {
            const float knockbackForce = 400.f;
            enemy->applyKnockback(knockbackForce * direction);
        }
    }
}

// -----------------------------------------------------
// Draw (Debug Visualisation)
// -----------------------------------------------------

/**
 * @brief Renders a red debug outline of the collider.
 * @param window SFML window target.
 */
void AttackHitbox::draw(sf::RenderWindow& window)
{
    if (!hasCollider()) return;

    sf::RectangleShape debugRect;
    debugRect.setSize(getCollider()->getSize());
    debugRect.setPosition(getPosition() + getCollider()->getOffset());
    debugRect.setFillColor(sf::Color::Transparent);
    debugRect.setOutlineColor(sf::Color::Red);
    debugRect.setOutlineThickness(2.f);

    window.draw(debugRect);
}
