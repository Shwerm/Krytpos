/*
 * GameObject.cpp - Kryptos Game Object Implementation
 * ---------------------------------------------------
 * Implements the GameObject class, managing properties and debug tracking.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - GameObject.h: Header for the GameObject class.
 *   - GameObjectManager.h: Manages registration of game objects.
 */

#include "../Include/GameObjectSystem/GameObject.h"
#include "../Include/GameObjectSystem/GameObjectManager.h"

 /**
  * @brief Constructs a GameObject and registers it with the GameObjectManager.
  * @param name Name of the game object.
  * @param position Initial position of the object.
  * @param active Whether the object is active.
  * @param rotation Initial rotation of the object.
  * @param mass Mass of the object.
  * @param useGravity Whether the object is affected by gravity.
  */
GameObject::GameObject(const std::string& name,
    const sf::Vector2f& position,
    const bool& active,
    const sf::Angle& rotation,
    const float& mass,
    const bool& useGravity)
    : name(name), position(position), active(true), rotation(rotation), mass(mass), useGravity(true) {
    GameObjectManager::getInstance().registerObject(this);
}

/**
 * @brief Destructor for GameObject.
 * Unregisters the object from the GameObjectManager.
 */
GameObject::~GameObject() {
    GameObjectManager::getInstance().unregisterObject(this);
}

// Getters
std::string GameObject::getName() const {
    return name;
}

sf::Vector2f GameObject::getPosition() const {
    return position;
}

bool GameObject::isActive() const {
    return active;
}

float GameObject::getMass() const {
    return mass;
}

bool GameObject::getUseGravity() const {
    return useGravity;
}

sf::Angle GameObject::getRotation() const {
    return rotation;
}

// Setters
void GameObject::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
}

void GameObject::setActive(bool state) {
    active = state;
}

void GameObject::setMass(float newMass) {
    mass = newMass;
}

void GameObject::setUseGravity(bool state) {
    useGravity = state;
}

void GameObject::setRotation(const sf::Angle& newRotation) {
    rotation = newRotation;
}
