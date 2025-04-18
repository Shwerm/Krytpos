/**
 * @file GameObject.h
 * @brief Base class for all game entities in the Kryptos Engine.
 *
 * @ingroup GameObjectSystem
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <functional>
#include <type_traits>
#include <optional>

#include "../2DCollider/Collider2D.h"
#include "../Physics/PhysicsConstants.h"

 /**
  * @class GameObject
  * @brief Abstract base class for all in-game objects.
  *
  * Handles transform, physics properties, and debug tracking for derived objects.
  */
class GameObject
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs a GameObject with given transform and physics properties.
     */
    GameObject(const std::string& name,
        const sf::Vector2f& position,
        const bool& active,
        const sf::Angle& rotation,
        const float& mass,
        const bool& useGravity);

    /**
     * @brief Virtual destructor for polymorphic behaviour.
     */
    virtual ~GameObject();

    // -----------------------------------------------------
    // Virtual Methods
    // -----------------------------------------------------

    /**
     * @brief Called every frame to update object logic.
     * @param deltaTime Time elapsed since last frame.
     */
    virtual void update(float deltaTime);

    /**
     * @brief Called at fixed intervals for physics-based updates.
     * @param fixedDeltaTime Fixed time step.
     */
    virtual void fixedUpdate(float fixedDeltaTime);

    /**
     * @brief Renders the object to the screen (optional override).
     * @param window Target SFML render window.
     */
    virtual void draw(sf::RenderWindow& window) {}

    /**
     * @brief Returns a map of debug-tracked variable names and their string representations.
     */
    virtual const std::unordered_map<std::string, std::function<std::string()>>& getDebugTrackedValues() const;

    // -----------------------------------------------------
    // Getters
    // -----------------------------------------------------

    std::string getName() const;
    sf::Vector2f getPosition() const;
    bool isActive() const;
    float getMass() const;
    bool getUseGravity() const;
    sf::Angle getRotation() const;
    sf::Vector2f getVelocity() const;
    bool hasCollider() const;
    Collider2D* getCollider();

    // -----------------------------------------------------
    // Setters
    // -----------------------------------------------------

    void setPosition(const sf::Vector2f& newPosition);
    void setActive(bool state);
    void setMass(float newMass);
    void setUseGravity(bool state);
    void setRotation(const sf::Angle& newRotation);
    void setVelocity(const sf::Vector2f& newVelocity);

    /**
     * @brief Adds a collider to the GameObject.
     * @param size Dimensions of the collider.
     * @param offset Local offset from the object's origin.
     */
    void addCollider(const sf::Vector2f& size, const sf::Vector2f& offset = { 0.f, 0.f });

protected:
    // -----------------------------------------------------
    // Protected Template Helpers
    // -----------------------------------------------------

    /**
     * @brief Registers a variable for runtime debug tracking.
     * @tparam T Type of the variable.
     * @param name Display name in debug window.
     * @param variable Reference to the variable to track.
     */
    template <typename T>
    void registerDebugVariable(const std::string& name, T& variable);

    // -----------------------------------------------------
    // Protected Members
    // -----------------------------------------------------

    std::string name; ///< Name of the object.
    sf::Vector2f position; ///< Position in world space.
    sf::Angle rotation; ///< Rotation of the object.
    bool active; ///< Whether the object is currently active.
    float mass; ///< Mass used for physics calculations.
    bool useGravity; ///< If true, gravity will affect this object.
    sf::Vector2f velocity; ///< Current velocity vector.
    std::optional<Collider2D> collider; ///< Optional 2D collider for physics.

private:
    std::unordered_map<std::string, std::function<std::string()>> debugTrackedValues; ///< Registered debug variables.
};

// ---------------------------------------------------------
// Template Implementation
// ---------------------------------------------------------

template <typename T>
void GameObject::registerDebugVariable(const std::string& name, T& variable)
{
    debugTrackedValues[name] = [&variable]() -> std::string
        {
            if constexpr (std::is_same_v<T, bool>)
            {
                return variable ? "true" : "false";
            }
            else
            {
                return std::to_string(variable);
            }
        };
}
