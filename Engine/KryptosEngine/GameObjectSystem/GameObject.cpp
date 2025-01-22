/*
Game Object Source - Krytpos - Sam Camilleri, Mural Studios
Dependencies: GameObject.h
*/

#include "GameObject.h"

// Constructor implementation
GameObject::GameObject(const std::string& name, const sf::Vector2f& position)
    : name(name), position(position), active(true) {}

// Set position
void GameObject::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
}

// Get position
sf::Vector2f GameObject::getPosition() const {
    return position;
}

// Get active state
bool GameObject::isActive() const {
    return active;
}

// Set active state
void GameObject::setActive(bool state) {
    active = state;
}

