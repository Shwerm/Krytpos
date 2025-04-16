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
    : GameObject(name, position, true, sf::degrees(0), 1.0f, true),
	health(100.f),
	movementSpeed(200.f),
	attackMultiplier(1.f),
	spriteRenderer(name)
{

    // Debug tracking registration
    registerDebugVariable("Health", this->health);
    registerDebugVariable("Speed", this->movementSpeed);
    registerDebugVariable("AttackMultiplier", this->attackMultiplier);
}

void EnemyClass::update(float deltaTime) {
    GameObject::update(deltaTime); // include physics, gravity, etc.

    // Basic movement logic (optional)
    position.x += movementSpeed * deltaTime;
    spriteRenderer.setPosition(position);
}

void EnemyClass::draw(sf::RenderWindow& window) {
    window.draw(spriteRenderer);
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

const sf::Sprite& EnemyClass::getSpriteRenderer() const {
    return spriteRenderer;
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
