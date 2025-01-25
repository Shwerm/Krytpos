#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <functional>
#include <type_traits>

class GameObject {
private:
    std::unordered_map<std::string, std::function<std::string()>> debugTrackedValues; // Map of debug-tracked variables

protected:
    std::string name;
    sf::Vector2f position;
    sf::Angle rotation;
    bool active;
    float mass;
    bool useGravity;

    // Register a debug-tracked variable
    template <typename T>
    void registerDebugVariable(const std::string& name, T& variable) {
        debugTrackedValues[name] = [&variable]() -> std::string {
            if constexpr (std::is_same_v<T, bool>) {
                return variable ? "true" : "false";
            }
            else {
                return std::to_string(variable);
            }
            };
    }

public:
    GameObject(
        const std::string& name,
        const sf::Vector2f& position,
        const bool& active,
        const sf::Angle& rotation,
        const float& mass,
        const bool& useGravity
    );

    virtual ~GameObject();

    // Retrieve debug-tracked variables
    const std::unordered_map<std::string, std::function<std::string()>>& getDebugTrackedValues() const {
        return debugTrackedValues;
    }

    // Getters
    std::string getName() const;
    sf::Vector2f getPosition() const;
    bool isActive() const;
    float getMass() const;
    bool getUseGravity() const;
    sf::Angle getRotation() const;

    // Setters
    void setPosition(const sf::Vector2f& newPosition);
    void setActive(bool state);
    void setMass(float newMass);
    void setUseGravity(bool state);
    void setRotation(const sf::Angle& newRotation);
};
