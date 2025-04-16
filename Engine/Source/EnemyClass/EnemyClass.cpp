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
    GameObject::fixedUpdate(fixedDeltaTime); // Apply gravity and velocity

    for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
        if (obj == this || !obj->hasCollider()) continue;

        if (Collider2D::intersects(*getCollider(), *obj->getCollider())) {
            const auto& b = obj->getCollider()->getBounds();
            const auto& a = getCollider()->getBounds();

            const float verticalThreshold = 5.f;
            bool landingFromAbove = (position.y + a.size.y <= b.position.y + verticalThreshold);

            if (landingFromAbove && velocity.y >= 0.f) {
                position.y = b.position.y - a.size.y;
                velocity.y = 0.f;
            }
        }
    }

    setPosition(position); // Update collider
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
