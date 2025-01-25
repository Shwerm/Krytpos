/*
Player class source - Kryptos - Sam Camilleri, Mural Studios
All Rights Reserved 2025.
Dependencies: Keyboard.hpp, Player.h
*/

#include <SFML/Window/Keyboard.hpp>
#include "../Include/PlayerClass/Player.h"


// Constructor & default player values
Player::Player(
    const std::string& name,
    const sf::Vector2f& position,
    const std::string& texturePath)
    : GameObject(
        name,
        position, 
        active, 
        rotation, 
        mass, 
        useGravity),
    health(100.f),
    attackSpeed(1.f),
    movementSpeed(200.f),
    attackMultiplier(1.f),
    jumpMultiplier(1.f),
    spriteRenderer() {
    spriteRenderer.loadTexture(texturePath);
    spriteRenderer.setPosition(position);

    // Register variables for debugging in debug window
    //registerDebugVariable("Health: ", health);
    registerDebugVariable("Attack Speed: ", attackSpeed);
    registerDebugVariable("Movement Speed: ", movementSpeed);
    registerDebugVariable("Attack Multiplier: ", attackMultiplier);
    registerDebugVariable("Jump Multiplier: ", jumpMultiplier);
}

// Update the player's logic
void Player::update(float deltaTime) {
    // Example of basic movement logic using arrow keys
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        movement.y -= movementSpeed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        movement.y += movementSpeed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        movement.x -= movementSpeed * deltaTime;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        movement.x += movementSpeed * deltaTime;
    }

    // Example jump logic
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        movement.y -= jumpMultiplier * 300.f * deltaTime; // Example jump force
    }

    // Update position
    position += movement;
    spriteRenderer.setPosition(position);
}

// Render the player
void Player::draw(sf::RenderWindow& window) {
    spriteRenderer.draw(window);
}

// Getters and setters for health
float Player::getHealth() const {
    return health;
}

void Player::setHealth(float value) {
    health = value;
}

// Getters and setters for attack speed
float Player::getAttackSpeed() const {
    return attackSpeed;
}

void Player::setAttackSpeed(float value) {
    attackSpeed = value;
}

// Getters and setters for movement speed
float Player::getMovementSpeed() const {
    return movementSpeed;
}

void Player::setMovementSpeed(float value) {
    movementSpeed = value;
}

// Getters and setters for attack multiplier
float Player::getAttackMultiplier() const {
    return attackMultiplier;
}

void Player::setAttackMultiplier(float value) {
    attackMultiplier = value;
}

// Getters and setters for jump multiplier
float Player::getJumpMultiplier() const {
    return jumpMultiplier;
}

void Player::setJumpMultiplier(float value) {
    jumpMultiplier = value;
}
