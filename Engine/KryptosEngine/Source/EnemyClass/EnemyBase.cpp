#include "../../Include/EnemyClass/EnemyBase.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"
#include <cmath>
#include <iostream>

EnemyBase::EnemyBase(const std::string& name,
    const sf::Vector2f& spawnPos,
    float patrolLeft,
    float patrolRight)
    : GameObject(name, spawnPos, true, sf::degrees(0), 1.0f, false),
    patrolLeft(patrolLeft),
    patrolRight(patrolRight),
    health(100.0f)
{
    registerDebugVariable("Health", health);
    registerDebugVariable("MovingRight", movingRight);
    registerDebugVariable("Cooldown", attackCooldownTimer);
}

void EnemyBase::update(float deltaTime) {
    if (!isActive()) return;

    if (isRecoiling) {
        recoilTimer -= deltaTime;
        if (recoilTimer <= 0.0f) {
            isRecoiling = false;
        }
        position += velocity * deltaTime;
        setPosition(position);
        if (spriteRenderer) spriteRenderer->setPosition(position);
        return;
    }

    attackCooldownTimer -= deltaTime;

    GameObject* player = nullptr;
    for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
        if (obj->getName() == "Player") {
            player = obj;
            break;
        }
    }

    if (!player) return;

    float dx = player->getPosition().x - position.x;
    float dy = player->getPosition().y - position.y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance <= attackRange) {
        faceDirection(dx);
        tryAttack(player->getPosition());
        velocity.x = 0.0f;
    }
    else {
        patrol(deltaTime);
    }

    position += velocity * deltaTime;
    setPosition(position);
    if (spriteRenderer) spriteRenderer->setPosition(position);
}

void EnemyBase::takeDamage(float amount) {
    health -= amount;
    if (health <= 0.f) {
        setActive(false);
        std::cout << "[" << name << "] Enemy has died.\n";
    }
}

bool EnemyBase::isAlive() const {
    return health > 0.f;
}

void EnemyBase::applyRecoil(const sf::Vector2f& force) {
    velocity = force;
    isRecoiling = true;
    recoilTimer = recoilDuration;
}

void EnemyBase::patrol(float deltaTime) {
    float dir = movingRight ? 1.f : -1.f;
    velocity.x = dir * moveSpeed;

    faceDirection(dir);

    if (position.x >= patrolRight)
        movingRight = false;
    else if (position.x <= patrolLeft)
        movingRight = true;
}

void EnemyBase::faceDirection(float directionX) {
    if (spriteRenderer && std::abs(directionX) > 0.01f) {
        spriteRenderer->setScale({ std::copysign(1.f, directionX), 1.f });
    }
}
