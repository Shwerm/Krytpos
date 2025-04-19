/**
 * @file GameObject.cpp
 * @brief Base class implementation for all interactive and updatable entities in the game world.
 *
 * @ingroup GameObjectSystem
 *
 * Manages transform, physics, and collider logic shared by all derived game entities.
 * Automatically registers and unregisters itself with the GameObjectManager.
 * Designed for extensibility and runtime interaction.
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/GameObjectSystem/GameObject.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"

 // -----------------------------------------------------
 // Constructor / Destructor
 // -----------------------------------------------------

 /**
  * @brief Constructs a GameObject with initial transform and physics values.
  * @param name Unique name identifier.
  * @param position Initial world position.
  * @param active Whether the object starts enabled.
  * @param rotation Starting rotation (in degrees).
  * @param mass Physical mass (affects gravity).
  * @param useGravity Whether the object should be affected by gravity.
  */
GameObject::GameObject(const std::string& name,
    const sf::Vector2f& position,
    const bool& active,
    const sf::Angle& rotation,
    const float& mass,
    const bool& useGravity)
    : name(name), position(position), active(active),
    rotation(rotation), mass(mass), useGravity(useGravity)
{
    GameObjectManager::getInstance().registerObject(this);
}

/**
 * @brief Automatically unregisters the object on destruction.
 */
GameObject::~GameObject()
{
    GameObjectManager::getInstance().unregisterObject(this);
}

// -----------------------------------------------------
// Runtime Update
// -----------------------------------------------------

/**
 * @brief Called every frame for general logic (visuals, animation, input).
 * @param deltaTime Elapsed time since last frame.
 */
void GameObject::update(float deltaTime)
{
    // Default implementation does nothing.
}

/**
 * @brief Called at a fixed timestep for physics simulation.
 * Applies gravity and updates position accordingly.
 * @param fixedDeltaTime Fixed physics timestep (in seconds).
 */
void GameObject::fixedUpdate(float fixedDeltaTime)
{
    if (!active) return;

    if (useGravity)
    {
        velocity.y += GRAVITY * fixedDeltaTime;
    }

    position += velocity * fixedDeltaTime;
}

// -----------------------------------------------------
// Getters
// -----------------------------------------------------

std::string GameObject::getName() const { return name; }
sf::Vector2f GameObject::getPosition() const { return position; }
bool GameObject::isActive() const { return active; }
float GameObject::getMass() const { return mass; }
bool GameObject::getUseGravity() const { return useGravity; }
sf::Angle GameObject::getRotation() const { return rotation; }
sf::Vector2f GameObject::getVelocity() const { return velocity; }

bool GameObject::hasCollider() const { return collider.has_value(); }

Collider2D* GameObject::getCollider()
{
    return collider ? &(*collider) : nullptr;
}

// -----------------------------------------------------
// Setters
// -----------------------------------------------------

void GameObject::setPosition(const sf::Vector2f& newPosition)
{
    position = newPosition;

    // Sync collider if it exists
    if (collider)
    {
        collider->setPosition(position);
    }
}

void GameObject::setActive(bool state) { active = state; }
void GameObject::setMass(float newMass) { mass = newMass; }
void GameObject::setUseGravity(bool state) { useGravity = state; }
void GameObject::setRotation(const sf::Angle& newRotation) { rotation = newRotation; }
void GameObject::setVelocity(const sf::Vector2f& newVelocity) { velocity = newVelocity; }

// -----------------------------------------------------
// Collider Setup
// -----------------------------------------------------

/**
 * @brief Adds a new collider to the object with size and offset.
 * @param size Width and height of the collider.
 * @param offset Local offset from object's origin.
 */
void GameObject::addCollider(const sf::Vector2f& size, const sf::Vector2f& offset)
{
    collider = Collider2D(size, offset);
    collider->setPosition(position);
}

// -----------------------------------------------------
// Debug Info
// -----------------------------------------------------

/**
 * @brief Returns a reference to all registered debug-tracked variables.
 * These can be rendered in the DebugWindow.
 * @return Map of string keys to stringified value functions.
 */
const std::unordered_map<std::string, std::function<std::string()>>& GameObject::getDebugTrackedValues() const
{
    return debugTrackedValues;
}
