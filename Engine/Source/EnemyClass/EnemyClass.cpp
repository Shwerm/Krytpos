/**
 * @file EnemyClass.cpp
 * @brief Implementation of the EnemyClass that handles AI behaviour and physics.
 *
 * @ingroup GameObjectSystem
 *
 * Provides patrol logic, grounding detection, knockback handling, and sprite management
 * for basic enemy AI in the Kryptos Engine platformer prototype.
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include "../../Include/EnemyClass/EnemyClass.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"
#include "../../Include/Physics/PhysicsConstants.h"

 // -----------------------------------------------------
 // Constructor
 // -----------------------------------------------------

EnemyClass::EnemyClass(const std::string& name,
    const sf::Vector2f& position,
    const std::string& texturePath)
    : GameObject(name, position, true, sf::degrees(0), 1.0f, true),
    health(100.f),
    movementSpeed(15.f),
    attackMultiplier(1.f),
    spriteRenderer(name)
{
    // Attempt to load sprite texture
    try {
        spriteRenderer.loadTexture(texturePath);

        // Set initial frame from sprite sheet
        sf::IntRect initialFrame;
        initialFrame.position = { 64, 36 };
        initialFrame.size = { 32, 38 };
        spriteRenderer.setTextureRect(initialFrame);
    }
    catch (const std::exception& e) {
        std::cerr << "[EnemyClass] Texture load error: " << e.what() << "\n";
        throw;
    }

    // Configure sprite and physics
    spriteRenderer.setPosition(position);
    spriteRenderer.setOrigin({ 16.f, 24.f });
    addCollider({ 24.f, 38.f }, { -10.f, -24.f });

    // Debug-tracked values
    registerDebugVariable("Health", health);
    registerDebugVariable("Speed", movementSpeed);
    registerDebugVariable("AttackMultiplier", attackMultiplier);
}

// -----------------------------------------------------
// Runtime Update (Visual Logic)
// -----------------------------------------------------

void EnemyClass::update(float deltaTime)
{
    spriteRenderer.setPosition(position);
}

// -----------------------------------------------------
// Fixed Update (Physics and AI)
// -----------------------------------------------------

void EnemyClass::fixedUpdate(float fixedDeltaTime)
{
    GameObject::fixedUpdate(fixedDeltaTime);

    if (!hasCollider()) return;

    auto* myCollider = getCollider();
    isGrounded = false;

    flipCooldown = std::max(0.f, flipCooldown - fixedDeltaTime);

    // -----------------------------------------------------
    // Ground Detection
    // -----------------------------------------------------
    for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
        if (!obj || obj == this || !obj->hasCollider()) continue;

        const auto myBounds = myCollider->getBounds();
        const auto otherBounds = obj->getCollider()->getBounds();
        const float verticalThreshold = 5.f;

        float myBottom = myBounds.position.y + myBounds.size.y;
        float platformTop = otherBounds.position.y;

        if (Collider2D::intersects(*myCollider, *obj->getCollider()) &&
            myBottom <= platformTop + verticalThreshold &&
            velocity.y >= 0.f)
        {
            position.y = platformTop - myBounds.size.y - (myBounds.position.y - position.y);
            velocity.y = 0.f;
            isGrounded = true;
        }
    }

    // -----------------------------------------------------
    // Patrol Logic
    // -----------------------------------------------------
    if (isGrounded) {
        float direction = movingLeft ? -1.f : 1.f;
        velocity.x = direction * movementSpeed;

        const auto bounds = myCollider->getBounds();

        // Probe just ahead of the foot to check for ground
        sf::Vector2f probePoint = {
            bounds.position.x + (movingLeft ? -1.f : bounds.size.x + 1.f),
            bounds.position.y + bounds.size.y + 1.f
        };

        bool groundAhead = false;
        for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
            if (!obj || obj == this || !obj->hasCollider()) continue;

            const auto groundBounds = obj->getCollider()->getBounds();
            if (probePoint.x >= groundBounds.position.x &&
                probePoint.x <= groundBounds.position.x + groundBounds.size.x &&
                probePoint.y >= groundBounds.position.y &&
                probePoint.y <= groundBounds.position.y + groundBounds.size.y)
            {
                groundAhead = true;
                break;
            }
        }

        // Turn around if no ground ahead
        if (!groundAhead && flipCooldown <= 0.f) {
            movingLeft = !movingLeft;
            velocity.x = 0.f;
            flipCooldown = flipCooldownDuration;
        }

        try {
            spriteRenderer.setScale({ movingLeft ? -1.f : 1.f, 1.f });
        }
        catch (...) {
            std::cerr << "[EnemyClass] spriteRenderer.setScale() threw unexpectedly!\n";
        }
    }

    // Apply movement
    position += velocity * fixedDeltaTime;
    setPosition(position);
}

// -----------------------------------------------------
// Rendering
// -----------------------------------------------------

void EnemyClass::draw(sf::RenderWindow& window)
{
    spriteRenderer.draw(window);

    bool showColliders = true;
    if (showColliders && hasCollider()) {
        getCollider()->drawDebug(window);
    }
}

// -----------------------------------------------------
// Getters
// -----------------------------------------------------

float EnemyClass::getHealth() const { return health; }
float EnemyClass::getMovementSpeed() const { return movementSpeed; }
float EnemyClass::getAttackMultiplier() const { return attackMultiplier; }

// -----------------------------------------------------
// Setters
// -----------------------------------------------------

void EnemyClass::setHealth(float value) { health = value; }
void EnemyClass::setMovementSpeed(float value) { movementSpeed = value; }
void EnemyClass::setAttackMultiplier(float value) { attackMultiplier = value; }

// -----------------------------------------------------
// Knockback
// -----------------------------------------------------

void EnemyClass::applyKnockback(const sf::Vector2f& force)
{
    velocity = force;
    movingLeft = false; // Disable AI for one frame
    flipCooldown = flipCooldownDuration;

    std::cout << "[Enemy] Knocked back with velocity (" << force.x << ", " << force.y << ")\n";
}
