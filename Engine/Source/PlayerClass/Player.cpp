#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

#include "../../Include/PlayerClass/Player.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"
#include "../../Include/Physics/PhysicsConstants.h"

Player::Player(
    const std::string& name,
    const sf::Vector2f& position,
    const std::string& texturePath)
    : GameObject(name, position, true, sf::degrees(0), 1.0f, true),
    health(100.f),
    attackSpeed(1.f),
    movementSpeed(200.f),
    attackMultiplier(1.f),
    jumpMultiplier(1.f),
    spriteRenderer(name)
{
    spriteRenderer.loadTexture(texturePath);
    spriteRenderer.setPosition(position);
    spriteRenderer.setOrigin({ 16.f, 24.f }); // Center for a 32x48 sprite

    addCollider({ 32.f, 48.f }, { 16.f, 0.f });

    registerDebugVariable("Health", health);
    registerDebugVariable("Attack Speed", attackSpeed);
    registerDebugVariable("Movement Speed", movementSpeed);
    registerDebugVariable("Attack Multiplier", attackMultiplier);
    registerDebugVariable("Jump Multiplier", jumpMultiplier);
}

void Player::update(float deltaTime) {
    sf::Vector2f inputVelocity(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        inputVelocity.x -= movementSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        inputVelocity.x += movementSpeed;
    }

    // Jumping
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isGrounded) {
        velocity.y = -jumpMultiplier * 170.f;
        isGrounded = false;
    }

    velocity.x = inputVelocity.x;

    // Apply movement + gravity
    GameObject::update(deltaTime);

    // Reset grounded state, will be updated if collision occurs
    isGrounded = false;

    // Ground collision detection
    for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
        if (obj == this || !obj->hasCollider()) continue;

        if (Collider2D::intersects(*getCollider(), *obj->getCollider())) {
            const auto& b = obj->getCollider()->getBounds();
            const auto& a = getCollider()->getBounds();

            const float verticalThreshold = 5.f;
            bool landingFromAbove = (position.y + a.size.y <= b.position.y + verticalThreshold);

            if (landingFromAbove && velocity.y >= 0.f) {
                position.y = b.position.y - a.size.y;
                velocity.y = 0.f;
                isGrounded = true;
            }
        }
    }

    // Sync position
    setPosition(position);
    spriteRenderer.setPosition(position);
}

void Player::draw(sf::RenderWindow& window) {
    spriteRenderer.draw(window);

    bool showColliders = true;
    if (showColliders && hasCollider()) {
        getCollider()->drawDebug(window);
    }
}

// Getter and Setter Implementations

float Player::getHealth() const { return health; }
void Player::setHealth(float value) { health = value; }

float Player::getAttackSpeed() const { return attackSpeed; }
void Player::setAttackSpeed(float value) { attackSpeed = value; }

float Player::getMovementSpeed() const { return movementSpeed; }
void Player::setMovementSpeed(float value) { movementSpeed = value; }

float Player::getAttackMultiplier() const { return attackMultiplier; }
void Player::setAttackMultiplier(float value) { attackMultiplier = value; }

float Player::getJumpMultiplier() const { return jumpMultiplier; }
void Player::setJumpMultiplier(float value) { jumpMultiplier = value; }
