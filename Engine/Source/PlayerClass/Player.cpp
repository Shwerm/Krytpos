#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "../../Include/PlayerClass/Player.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"
#include "../../Include/Physics/PhysicsConstants.h"
#include "../../Include/PlayerClass/AttackHitbox.h"
#include "../../Include/EnemyClass/EnemyClass.h"

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
    staminaSystem(100.f, 20.f)
{
    texturePathLeft = texturePathRight;
    const size_t dotPos = texturePathLeft.find_last_of('.');
    if (dotPos != std::string::npos) {
        texturePathLeft.insert(dotPos, "Reversed");
    }

    spriteRenderer.loadTexture(texturePathRight);
    spriteRenderer.setOrigin({ 0.f, 2.f });
    spriteRenderer.setPosition(position);

    addCollider({ 28.f, 48.f }, { 18.f, 0.f });

    registerDebugVariable("Health", health);
    registerDebugVariable("Attack Speed", attackSpeed);
    registerDebugVariable("Movement Speed", movementSpeed);
    registerDebugVariable("Attack Multiplier", attackMultiplier);
    registerDebugVariable("Jump Multiplier", jumpMultiplier);
}

void Player::update(float deltaTime) {
    sf::Vector2f inputVelocity(0.f, 0.f);

    staminaSystem.Update(deltaTime);
    damageCooldown = std::max(0.f, damageCooldown - deltaTime);

    checkDeath();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        inputVelocity.x -= movementSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        inputVelocity.x += movementSpeed;
    }

    bool currentPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    if (currentPressed && !previousMousePressed) {
        handleAttack();
    }
    previousMousePressed = currentPressed;

    if (inputVelocity.x < 0.f && isFacingRight) {
        isFacingRight = false;
        try { spriteRenderer.loadTexture(texturePathLeft); }
        catch (...) { std::cerr << "[Player] Failed to load flipped (left) texture.\n"; }
    }
    else if (inputVelocity.x > 0.f && !isFacingRight) {
        isFacingRight = true;
        try { spriteRenderer.loadTexture(texturePathRight); }
        catch (...) { std::cerr << "[Player] Failed to load right-facing texture.\n"; }
    }

    velocity.x = inputVelocity.x;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isGrounded) {
        velocity.y = -jumpMultiplier * 170.f;
        isGrounded = false;
    }

    GameObject::update(deltaTime);

    // Predictive vertical collision
    sf::Vector2f predictedPosition = position;
    predictedPosition.y += velocity.y * deltaTime;

    sf::FloatRect predictedBounds;
    predictedBounds.position = predictedPosition + getCollider()->getOffset();
    predictedBounds.size = getCollider()->getSize();

    bool groundedThisFrame = false;

    for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
        if (obj == this || !obj->hasCollider()) continue;

        sf::FloatRect otherBounds = obj->getCollider()->getBounds();

        // Manual AABB intersection (SFML 3.0 compatible)
        bool isIntersecting =
            predictedBounds.position.x < otherBounds.position.x + otherBounds.size.x &&
            predictedBounds.position.x + predictedBounds.size.x > otherBounds.position.x &&
            predictedBounds.position.y < otherBounds.position.y + otherBounds.size.y &&
            predictedBounds.position.y + predictedBounds.size.y > otherBounds.position.y;

        if (isIntersecting) {
            const float verticalThreshold = 5.f;
            float playerBottom = position.y + getCollider()->getSize().y;
            float platformTop = otherBounds.position.y;

            bool landingFromAbove = (playerBottom <= platformTop + verticalThreshold);

            if (landingFromAbove && velocity.y >= 0.f) {
                position.y = platformTop - getCollider()->getSize().y;
                velocity.y = 0.f;
                groundedThisFrame = true;
                break;
            }
        }
    }

    isGrounded = groundedThisFrame;

    if (!groundedThisFrame) {
        position.y += velocity.y * deltaTime;
    }

    // Damage from enemies
    for (auto* obj : GameObjectManager::getInstance().getGameObjects()) {
        if (obj == this || !obj->hasCollider()) continue;

        if (Collider2D::intersects(*getCollider(), *obj->getCollider())) {
            if (auto* enemy = dynamic_cast<EnemyClass*>(obj)) {
                if (damageCooldown <= 0.f) {
                    takeDamage(10.f);
                    damageCooldown = 1.f;
                }
            }
        }
    }

    // Death threshold and respawn
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

void Player::takeDamage(float amount) {
    health -= amount;
    if (health < 0.f) health = 0.f;
    std::cout << "[Player] Took " << amount << " damage. Current Health: " << health << "\n";
}

void Player::handleAttack() {
    const float staminaCost = 20.f;

    if (!staminaSystem.UseStamina(staminaCost)) {
        std::cout << "[Player] Not enough stamina to attack.\n";
        return;
    }

    const float halfColliderWidth = 32.f / 2.f;
    const float verticalCenterOffset = 48.f / 2.f;
    const float horizontalAdjustment = -32.f;

    sf::Vector2f offset = {
        isFacingRight ? (halfColliderWidth - horizontalAdjustment)
                      : -(halfColliderWidth + horizontalAdjustment),
        verticalCenterOffset
    };

    sf::Vector2f attackPos = getPosition() + offset;
    sf::Vector2f dir = isFacingRight ? sf::Vector2f(1.f, 0.f) : sf::Vector2f(-1.f, 0.f);

    auto* hitbox = new AttackHitbox("AttackHitbox", attackPos, dir);
    GameObjectManager::getInstance().registerObject(hitbox);
}

void Player::checkDeath() {
    if (health > 0.f)
        return;

    std::cout << "[Player] Died. Respawning...\n";
    health = maxHealth;
    staminaSystem.Reset();
    velocity = { 0.f, 0.f };
    setPosition(respawnPosition);
}
