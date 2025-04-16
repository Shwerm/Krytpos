#include "../../Include/GameObjectSystem/GameObject.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"

GameObject::GameObject(const std::string& name,
    const sf::Vector2f& position,
    const bool& active,
    const sf::Angle& rotation,
    const float& mass,
    const bool& useGravity)
    : name(name), position(position), active(active), rotation(rotation), mass(mass), useGravity(useGravity) {
    GameObjectManager::getInstance().registerObject(this);
}

GameObject::~GameObject() {
    GameObjectManager::getInstance().unregisterObject(this);
}

void GameObject::update(float deltaTime) {
    // For visual updates only
}

void GameObject::fixedUpdate(float fixedDeltaTime) {
    if (!active) return;

    if (useGravity) {
        velocity.y += GRAVITY * fixedDeltaTime;
    }

    position += velocity * fixedDeltaTime;
}

std::string GameObject::getName() const { return name; }
sf::Vector2f GameObject::getPosition() const { return position; }
bool GameObject::isActive() const { return active; }
float GameObject::getMass() const { return mass; }
bool GameObject::getUseGravity() const { return useGravity; }
sf::Angle GameObject::getRotation() const { return rotation; }
sf::Vector2f GameObject::getVelocity() const { return velocity; }
bool GameObject::hasCollider() const { return collider.has_value(); }
Collider2D* GameObject::getCollider() { return collider ? &*collider : nullptr; }

void GameObject::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
    if (collider) {
        collider->setPosition(newPosition);
    }
}

void GameObject::setActive(bool state) { active = state; }
void GameObject::setMass(float newMass) { mass = newMass; }
void GameObject::setUseGravity(bool state) { useGravity = state; }
void GameObject::setRotation(const sf::Angle& newRotation) { rotation = newRotation; }
void GameObject::setVelocity(const sf::Vector2f& newVelocity) { velocity = newVelocity; }

void GameObject::addCollider(const sf::Vector2f& size, const sf::Vector2f& offset) {
    collider = Collider2D(size, offset);
    collider->setPosition(position);
}

const std::unordered_map<std::string, std::function<std::string()>>& GameObject::getDebugTrackedValues() const {
    return debugTrackedValues;
}
