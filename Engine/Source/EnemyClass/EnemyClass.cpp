// EnemyClass.cpp - Kryptos Enemy Game Object Class Implementation

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../../Include/EnemyClass/EnemyClass.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"
#include "../../Include/Physics/PhysicsConstants.h"

EnemyClass::EnemyClass(
    const std::string& name,
    const sf::Vector2f& position,
    const std::string& texturePath)
    : GameObject(name, position, true, sf::degrees(0), 1.0f, false),
    health(100.f),
    movementSpeed(200.f),
    attackMultiplier(1.f),
    spriteRenderer(name)
{
    // Hardcoded sprite sheet frame: Walk Frame 1
    sf::IntRect initialFrame;
    initialFrame.position = { , -1 };
    initialFrame.size = { 32, 48 };


    spriteRenderer.loadTexture(texturePath);
    spriteRenderer.setTextureRect(initialFrame);
    spriteRenderer.setPosition(position);
    spriteRenderer.setOrigin({ 16.f, 24.f }); // Centered origin

    addCollider({ 32.f, 48.f }, { 16.f, 0.f });

    // Debug tracking
    registerDebugVariable("Health", health);
    registerDebugVariable("Speed", movementSpeed);
    registerDebugVariable("AttackMultiplier", attackMultiplier);
}

void EnemyClass::update(float deltaTime) {
    GameObject::update(deltaTime); // Apply gravity and velocity

    // Basic movement logic (placeholder)
    spriteRenderer.setPosition(position);
}

void EnemyClass::draw(sf::RenderWindow& window) {
    spriteRenderer.draw(window);

    bool showColliders = true;
    if (showColliders && hasCollider()) {
        getCollider()->drawDebug(window);
    }
}

// Getters
float EnemyClass::getHealth() const {
    return health;
}

float EnemyClass::getMovementSpeed() const {
    return movementSpeed;
}

float EnemyClass::getAttackMultiplier() const {
    return attackMultiplier;
}

// Setters
void EnemyClass::setHealth(float value) {
    health = value;
}

void EnemyClass::setMovementSpeed(float value) {
    movementSpeed = value;
}

void EnemyClass::setAttackMultiplier(float value) {
    attackMultiplier = value;
}
