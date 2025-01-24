/*
Game Object Source - Krytpos - Sam Camilleri, Mural Studios
All Rights Reserved 2025.
Dependencies: GameObject.h
*/

#include "../Include/GameObjectSystem/GameObject.h"
#include "../include/GameObjectSystem/GameObjectManager.h"

// Constructor
GameObject::GameObject(const std::string& name, const sf::Vector2f& position)
    : name(name), position(position), active(true) {
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

// Setters
void GameObject::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
}

void GameObject::setActive(bool state) {
    active = state;
}


