// GameObject.h - Kryptos Game Object Class
#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <functional>
#include <type_traits>
#include <optional>
#include "../2DCollider/Collider2D.h"
#include "../Physics/PhysicsConstants.h"

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
    sf::Vector2f velocity;
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

    virtual void update(float deltaTime);

    std::string getName() const;
    sf::Vector2f getPosition() const;
    bool isActive() const;
    float getMass() const;
    bool getUseGravity() const;
    sf::Angle getRotation() const;
    sf::Vector2f getVelocity() const;
    bool hasCollider() const;
    Collider2D* getCollider();

    void setPosition(const sf::Vector2f& newPosition);
    void setActive(bool state);
    void setMass(float newMass);
    void setUseGravity(bool state);
    void setRotation(const sf::Angle& newRotation);
    void setVelocity(const sf::Vector2f& newVelocity);
    void addCollider(const sf::Vector2f& size, const sf::Vector2f& offset = { 0.f, 0.f });

    virtual const std::unordered_map<std::string, std::function<std::string()>>& getDebugTrackedValues() const;
};

// Template definition must be outside the class body
template <typename T>
void GameObject::registerDebugVariable(const std::string& name, T& variable) {
    debugTrackedValues[name] = [&variable]() -> std::string {
        if constexpr (std::is_same_v<T, bool>) {
            return variable ? "true" : "false";
        }
        else {
            return std::to_string(variable);
        }
        };
}
