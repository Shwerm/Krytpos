// GameObject.h - Additions for gravity system integration
#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <functional>
#include <type_traits>
#include <optional>
#include "../2DCollider/Collider2D.h"
#include "../Physics/PhysicsConstants.h" // <-- NEW include for gravity

class GameObject {
private:
    std::unordered_map<std::string, std::function<std::string()>> debugTrackedValues;

protected:
    std::string name;
    sf::Vector2f position;
    sf::Angle rotation;
    bool active;
    float mass;
    bool useGravity;
    sf::Vector2f velocity; ///< Object velocity (used for gravity and movement)
    std::optional<Collider2D> collider;

    template <typename T>
    void registerDebugVariable(const std::string& name, T& variable);

public:
    GameObject(const std::string& name,
        const sf::Vector2f& position,
        const bool& active,
        const sf::Angle& rotation,
        const float& mass,
        const bool& useGravity);

    virtual ~GameObject();

    // Core update method
    virtual void update(float deltaTime); // <-- NEW

    // Getters
    std::string getName() const;
    sf::Vector2f getPosition() const;
    bool isActive() const;
    float getMass() const;
    bool getUseGravity() const;
    sf::Angle getRotation() const;
    sf::Vector2f getVelocity() const; // <-- NEW
    bool hasCollider() const;
    Collider2D* getCollider();

    // Setters
    void setPosition(const sf::Vector2f& newPosition);
    void setActive(bool state);
    void setMass(float newMass);
    void setUseGravity(bool state);
    void setRotation(const sf::Angle& newRotation);
    void setVelocity(const sf::Vector2f& newVelocity); // <-- NEW
    void addCollider(const sf::Vector2f& size, const sf::Vector2f& offset = { 0.f, 0.f });
};
