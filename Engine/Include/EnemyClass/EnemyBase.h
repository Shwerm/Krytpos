#pragma once

#include "../GameObjectSystem/GameObject.h"
#include "../SpriteRenderingSystem/SpriteRenderer.h"
#include <memory>

class EnemyBase : public GameObject {
public:
    EnemyBase(const std::string& name,
        const sf::Vector2f& spawnPos,
        float patrolLeft,
        float patrolRight);

    virtual ~EnemyBase() = default;

    void update(float deltaTime) override;

    void takeDamage(float amount);
    void applyRecoil(const sf::Vector2f& force);

    bool isAlive() const;

protected:
    virtual void tryAttack(const sf::Vector2f& playerPos) = 0;

    void patrol(float deltaTime);
    void faceDirection(float directionX);

    float attackCooldownTimer = 0.0f;
    float attackRange = 64.0f;

    float moveSpeed = 60.0f;
    bool movingRight = true;

    bool isRecoiling = false;
    float recoilDuration = 0.3f;
    float recoilTimer = 0.0f;

    float patrolLeft;
    float patrolRight;

    float health = 100.0f;

    std::unique_ptr<SpriteRenderer> spriteRenderer;
};
