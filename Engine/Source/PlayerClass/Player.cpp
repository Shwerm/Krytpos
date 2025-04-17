#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

#include "../../Include/PlayerClass/Player.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"
#include "../../Include/Physics/PhysicsConstants.h"
#include "../../Include/PlayerClass/AttackHitbox.h"


Player::Player(
    const std::string& name,
    const sf::Vector2f& position,
    const std::string& texturePathRight)
    : GameObject(name, position, true, sf::degrees(0), 1.0f, true),
    health(100.f),
    maxHealth(100.f),
    attackSpeed(1.f),
    movementSpeed(200.f),
    attackMultiplier(1.f),
    jumpMultiplier(1.f),
    spriteRenderer(name),
    respawnPosition(position),
    texturePathRight(texturePathRight),
	staminaSystem(100.f, 10.f) // Initialise stamina system with max stamina and regen rate
{
    // Build left-facing texture path based on naming convention
    texturePathLeft = texturePathRight;
    const size_t dotPos = texturePathLeft.find_last_of('.');
    if (dotPos != std::string::npos) {
        texturePathLeft.insert(dotPos, "Reversed");
    }

    // Load default (facing right)
    spriteRenderer.loadTexture(texturePathRight);
    spriteRenderer.setOrigin({ 0.f, 2.f });
    spriteRenderer.setPosition(position);

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
    bool currentPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    if (currentPressed && !previousMousePressed) {
        handleAttack(); // Trigger only on press
    }

    previousMousePressed = currentPressed;


    // Switch textures based on movement direction
    if (inputVelocity.x < 0.f && isFacingRight) {
        isFacingRight = false;
        try {
            spriteRenderer.loadTexture(texturePathLeft);
        }
        catch (...) {
            std::cerr << "[Player] Failed to load flipped (left) texture.\n";
        }
    }
    else if (inputVelocity.x > 0.f && !isFacingRight) {
        isFacingRight = true;
        try {
            spriteRenderer.loadTexture(texturePathRight);
        }
        catch (...) {
            std::cerr << "[Player] Failed to load right-facing texture.\n";
        }
    }

    velocity.x = inputVelocity.x;

    // Jumping
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isGrounded) {
        velocity.y = -jumpMultiplier * 170.f;
        isGrounded = false;
    }

    GameObject::update(deltaTime);
    isGrounded = false;

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

    if (position.y > fallThresholdY) {
        position = respawnPosition;
		health = maxHealth;
        staminaSystem.Reset();
        velocity = { 0.f, 0.f };
    }



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

void Player::setRespawnPosition(const sf::Vector2f& position) {
    respawnPosition = position;
}

float Player::getHealth() const { return health; }
void Player::setHealth(float value) { health = value; }

float Player::getMaxHealth() const { return maxHealth; }
void Player::setMaxHealth(float value) { maxHealth = value; }

float Player::getAttackSpeed() const { return attackSpeed; }
void Player::setAttackSpeed(float value) { attackSpeed = value; }

float Player::getMovementSpeed() const { return movementSpeed; }
void Player::setMovementSpeed(float value) { movementSpeed = value; }

float Player::getAttackMultiplier() const { return attackMultiplier; }
void Player::setAttackMultiplier(float value) { attackMultiplier = value; }

float Player::getJumpMultiplier() const { return jumpMultiplier; }
void Player::setJumpMultiplier(float value) { jumpMultiplier = value; }

float Player::getStamina() const {
    return staminaSystem.GetStamina();
}

float Player::getMaxStamina() const {
    return staminaSystem.GetMaxStamina();
}

float Player::getStaminaRatio() const {
    return staminaSystem.GetStaminaRatio();
}

void Player::handleAttack() {
    const float staminaCost = 20.f;

    if (!staminaSystem.UseStamina(staminaCost)) {
        std::cout << "[Player] Not enough stamina to attack.\n";
        return;
    }

    sf::Vector2f attackPos = position + sf::Vector2f(isFacingRight ? 32.f : -32.f, 0.f);
    sf::Vector2f dir = isFacingRight ? sf::Vector2f(1.f, 0.f) : sf::Vector2f(-1.f, 0.f);

    auto* hitbox = new AttackHitbox("AttackHitbox", attackPos, dir);
    GameObjectManager::getInstance().registerObject(hitbox);
}


