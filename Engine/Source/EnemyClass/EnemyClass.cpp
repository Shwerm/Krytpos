#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../../Include/EnemyClass/EnemyClass.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"
#include "../../Include/Physics/PhysicsConstants.h"

EnemyClass::EnemyClass(
    const std::string& name,
    const sf::Vector2f& position,
    const std::string& texturePath)
    : GameObject(name, position, true, sf::degrees(0), 1.0f, true),
    health(100.f),
    movementSpeed(200.f),
    attackMultiplier(1.f),
    spriteRenderer(name)
{
    sf::IntRect initialFrame;
    initialFrame.position = { 64, 36 };
    initialFrame.size = { 32, 38 };

    spriteRenderer.loadTexture(texturePath);
    spriteRenderer.setTextureRect(initialFrame);
    spriteRenderer.setPosition(position);
    spriteRenderer.setOrigin({ 16.f, 24.f });

    addCollider({ 32.f, 38.f }, { -16.f, -24.f });

    registerDebugVariable("Health", health);
    registerDebugVariable("Speed", movementSpeed);
    registerDebugVariable("AttackMultiplier", attackMultiplier);
}

void EnemyClass::update(float deltaTime) {
    // No physics here anymore — visuals only
    spriteRenderer.setPosition(position);
}

void EnemyClass::fixedUpdate(float fixedDeltaTime) {
    GameObject::fixedUpdate(fixedDeltaTime); // Apply gravity

    if (!hasCollider()) return;
    auto* myCollider = getCollider();
    const auto myBounds = myCollider->getBounds();

    isGrounded = false;

    for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
        if (obj == this || !obj->hasCollider()) continue;

        const auto otherBounds = obj->getCollider()->getBounds();

        if (Collider2D::intersects(*myCollider, *obj->getCollider())) {
            const float verticalThreshold = 5.f;

            const float myBottom = myBounds.position.y + myBounds.size.y;
            const float platformTop = otherBounds.position.y;

            const bool landingFromAbove = (myBottom <= platformTop + verticalThreshold);

            if (landingFromAbove && velocity.y >= 0.f) {
                position.y = platformTop - myBounds.size.y - (myBounds.position.y - position.y);
                velocity.y = 0.f;
                isGrounded = true;
            }
        }
    }

    // --- Patrolling logic (only if grounded)
    if (isGrounded) {
        float direction = movingLeft ? -1.f : 1.f;
        velocity.x = direction * movementSpeed;

        // Edge detection box
        sf::Vector2f probeOffset = { direction * myBounds.size.x * 0.6f, 2.f }; // just ahead of feet
        sf::Vector2f probePoint = { myBounds.position.x + probeOffset.x, myBounds.position.y + myBounds.size.y + probeOffset.y };

        bool hasGround = false;
        for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
            if (obj == this || !obj->hasCollider()) continue;

            const auto bounds = obj->getCollider()->getBounds();

            if (probePoint.x >= bounds.position.x &&
                probePoint.x <= bounds.position.x + bounds.size.x &&
                probePoint.y >= bounds.position.y &&
                probePoint.y <= bounds.position.y + bounds.size.y) {
                hasGround = true;
                break;
            }
        }

        if (!hasGround) {
            movingLeft = !movingLeft; // Flip patrol direction
            velocity.x = 0.f;
        }

        // Flip sprite if needed
        spriteRenderer.setScale({ movingLeft ? -1.f : 1.f, 1.f });
    }

    position += velocity * fixedDeltaTime;
    setPosition(position); // sync collider
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
