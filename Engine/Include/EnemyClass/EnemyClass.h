#pragma once

#include "EnemyBase.h"

class EnemyClass : public EnemyBase {
public:
    EnemyClass(const std::string& name,
        const sf::Vector2f& spawnPos,
        float patrolLeft,
        float patrolRight);

    void draw(sf::RenderWindow& window) override;


protected:
    void tryAttack(const sf::Vector2f& playerPos) override;

private:
    float attackCooldown = 1.0f;
};
