/*
 * Player.cpp - Kryptos Player Implementation
 * ------------------------------------------
 * Implements the Player class, handling logic, movement, and rendering.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - Keyboard.hpp: For handling player input.
 *   - Player.h: Header for the Player class.
 */

#include <SFML/Window/Keyboard.hpp>
#include "../Include/PlayerClass/Player.h"

 /**
  * @brief Constructs a Player object with default attributes.
  *
  * Loads the player's texture, initializes its sprite renderer, and registers debug-tracked variables.
  * @param name The name of the player.
  * @param position The initial position of the player.
  * @param texturePath Path to the texture used for the player's sprite.
  */
Player::Player(
    const std::string& name,
    const sf::Vector2f& position,
    const std::string& texturePath)
    : GameObject(name, position, active, rotation, mass, useGravity),
    health(100.f),
    attackSpeed(1.f),
    movementSpeed(200.f),
    attackMultiplier(1.f),
    jumpMultiplier(1.f),
    spriteRenderer() {
    spriteRenderer.loadTexture(texturePath);
    spriteRenderer.setPosition(position);

    // Register variables for debugging in the debug window
    registerDebugVariable("Health: ", health);
    registerDebugVariable("Attack Speed: ", attackSpeed);
    registerDebugVariable("Movement Speed: ", movementSpeed);
    registerDebugVariable("Attack Multiplier: ", attackMultiplier);
    registerDebugVariable("Jump Multiplier: ", jumpMultiplier);
}

/**
 * @brief Updates the player's logic, including movement and input handling.
 * @param deltaTime Time elapsed since the last frame.
 */
void Player::update(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    // Handle movement input
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

    // Handle jump input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        movement.y -= jumpMultiplier * 300.f * deltaTime; // Example jump force
    }

    // Update position and sprite
    position += movement;
    spriteRenderer.setPosition(position);
}

/**
 * @brief Renders the player using the provided render window.
 * @param window The render window where the player is drawn.
 */
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
