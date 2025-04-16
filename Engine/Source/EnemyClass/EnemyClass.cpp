#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp> 
#include <iostream>

#include "../../Include/EnemyClass/EnemyClass.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"
#include "../../Include/Physics/PhysicsConstants.h"

EnemyClass::EnemyClass(
    const std::string& name,
    const sf::Vector2f& position,
    const std::string& texturePath)
    : GameObject(name, position, true, sf::degrees(0), 1.0f, true),
    health(100.f),
    movementSpeed(15.f),
    attackMultiplier(1.f),
    spriteRenderer(name)
{
    std::cout << "[EnemyClass] constructor start\n";

    // Attempt to load texture with crash safety
    try {
        spriteRenderer.loadTexture(texturePath);

        sf::IntRect initialFrame;
        initialFrame.position = { 64, 36 };
        initialFrame.size = { 32, 38 };

        spriteRenderer.setTextureRect(initialFrame);
    }
    catch (const std::exception& e) {
        std::cerr << "[EnemyClass] Texture load error: " << e.what() << "\n";
        throw; // Rethrow so engine-level handler can catch and log it
    }

    spriteRenderer.setPosition(position);
    spriteRenderer.setOrigin({ 16.f, 24.f });

    addCollider({ 24.f, 38.f }, { -10.f, -24.f });

    registerDebugVariable("Health", health);
    registerDebugVariable("Speed", movementSpeed);
    registerDebugVariable("AttackMultiplier", attackMultiplier);

    std::cout << "[EnemyClass] constructor end\n";
}




void EnemyClass::update(float deltaTime) {
    // No physics here anymore — visuals only
    spriteRenderer.setPosition(position);
}

void EnemyClass::fixedUpdate(float fixedDeltaTime) {
    GameObject::fixedUpdate(fixedDeltaTime); // Apply gravity

    if (!hasCollider()) return;

    auto* myCollider = getCollider();
    isGrounded = false;

    // Decrease flip cooldown timer
    flipCooldown = std::max(0.f, flipCooldown - fixedDeltaTime);

    // --- Grounding logic
    for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
        if (!obj || obj == this || !obj->hasCollider()) continue;

    std::cout << "[EnemyClass] Gravity + Collider check passed\n";
        const auto myBounds = myCollider->getBounds();
        const auto otherBounds = obj->getCollider()->getBounds();

        const float verticalThreshold = 5.f;

        const float myBottom = myBounds.position.y + myBounds.size.y;
        const float platformTop = otherBounds.position.y;

        if (Collider2D::intersects(*myCollider, *obj->getCollider()) &&
            myBottom <= platformTop + verticalThreshold &&
            velocity.y >= 0.f) {
            position.y = platformTop - myBounds.size.y - (myBounds.position.y - position.y);
            velocity.y = 0.f;
            isGrounded = true;
        }
    }

    //// --- Patrolling logic
    if (isGrounded) {
        float direction = movingLeft ? -1.f : 1.f;
        velocity.x = direction * movementSpeed;

        const auto bounds = getCollider()->getBounds(); // Re-fetch after gravity/grounding

        // Small probe point just ahead of forward foot
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
                probePoint.y <= groundBounds.position.y + groundBounds.size.y) {
                groundAhead = true;
                break;
            }
        }

        if (!groundAhead && flipCooldown <= 0.f) {
            movingLeft = !movingLeft;
            velocity.x = 0.f;
            flipCooldown = flipCooldownDuration;
        }

        // Safely flip sprite scale
        try {
           spriteRenderer.setScale({ movingLeft ? -1.f : 1.f, 1.f });
        }
        catch (...) {
            std::cerr << "[EnemyClass] spriteRenderer.setScale() threw unexpectedly!\n";
        }
    }

    //// Apply final movement
    position += velocity * fixedDeltaTime;
    setPosition(position); // Sync collider

    // --- Debug logs
    /*std::cout << "[EnemyClass] Pos: (" << position.x << ", " << position.y << ")"
        << " | Vel: (" << velocity.x << ", " << velocity.y << ")"
        << " | Grounded: " << (isGrounded ? "Yes" : "No") << "\n";*/
}

void EnemyClass::draw(sf::RenderWindow& window) {
    spriteRenderer.draw(window);

    bool showColliders = true;
    if (showColliders && hasCollider()) {
        getCollider()->drawDebug(window);
    }
}

// Getters
float EnemyClass::getHealth() const { return health; }
float EnemyClass::getMovementSpeed() const { return movementSpeed; }
float EnemyClass::getAttackMultiplier() const { return attackMultiplier; }

// Setters
void EnemyClass::setHealth(float value) { health = value; }
void EnemyClass::setMovementSpeed(float value) { movementSpeed = value; }
void EnemyClass::setAttackMultiplier(float value) { attackMultiplier = value; }
