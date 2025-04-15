#include "../../Include/EnemyClass/EnemyClass.h"
#include <iostream>

EnemyClass::EnemyClass(const std::string& name,
    const sf::Vector2f& spawnPos,
    float patrolLeft,
    float patrolRight)
    : EnemyBase(name, spawnPos, patrolLeft, patrolRight)
{
    spriteRenderer = std::make_unique<SpriteRenderer>(name);
    spriteRenderer->loadTexture("Assets/EngineAssets/Textures/Enemies/EnemySpriteSheet.png"); // Update path
    spriteRenderer->setPosition(spawnPos);

    addCollider({ 32.f, 48.f }); // Example collider size
}

void EnemyClass::draw(sf::RenderWindow& window) {
    if (spriteRenderer) {
        spriteRenderer->draw(window);
    }
}


void EnemyClass::tryAttack(const sf::Vector2f& playerPos) {
    if (attackCooldownTimer > 0.0f)
        return;

    attackCooldownTimer = attackCooldown;

    std::cout << "[EnemyMelee] Attack at " << playerPos.x << ", " << playerPos.y << "\n";

    // Future: spawn a hitbox here, or check overlap with player
}
