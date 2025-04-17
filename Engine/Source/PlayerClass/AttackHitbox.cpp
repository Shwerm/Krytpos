#include "../../Include/PlayerClass/AttackHitbox.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"
#include "../../Include/EnemyClass/EnemyClass.h"
#include <iostream>

AttackHitbox::AttackHitbox(const std::string& name, const sf::Vector2f& position, const sf::Vector2f& direction)
    : GameObject(name, position, true, sf::degrees(0), 0.f, false), direction(direction)
{
    addCollider({ 32.f, 32.f }, { -16.f, -16.f }); // Centered box
    getCollider()->setPosition(position);
}

void AttackHitbox::update(float deltaTime)
{
    lifetime -= deltaTime;
    if (lifetime <= 0.f)
    {
        GameObjectManager::getInstance().unregisterObject(this);
        delete this;
        return;
    }

    for (auto* obj : GameObjectManager::getInstance().getGameObjects())
    {
        if (obj == this || !obj->hasCollider()) continue;

        auto* enemy = dynamic_cast<EnemyClass*>(obj);
        if (enemy && Collider2D::intersects(*getCollider(), *enemy->getCollider()))
        {
            // Knockback vector (scaled)
            const float knockbackForce = 400.f;
            enemy->applyKnockback(knockbackForce * direction);
        }
    }
}
