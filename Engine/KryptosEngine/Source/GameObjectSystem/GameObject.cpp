/*
Game Object Source - Krytpos - Sam Camilleri, Mural Studios
All Rights Reserved 2025.
Dependencies: GameObject.h
*/

#include "../Include/GameObjectSystem/GameObject.h"
#include "../include/GameObjectSystem/GameObjectManager.h"

// Constructor
GameObject::GameObject(
    const std::string& name, 
    const sf::Vector2f& position, 
    const bool& active, 
    const sf::Angle& rotation, 
    const float& mass, 
    const bool& useGravity)
    : 
    name(name), 
    position(position), 
    active(true), 
    rotation(rotation), 
    mass(mass), 
    useGravity(true)
{
    GameObjectManager::getInstance().registerObject(this);
}

// Destructor
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


