/*
 * GameObject.h - Kryptos Game Object Class
 * ----------------------------------------
 * Defines the base GameObject class used to represent entities in the game.
 * Supports properties such as position, rotation, mass, and debug tracking.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include <functional>
#include <type_traits>

 /**
  * @class GameObject
  * @brief Base class for game objects in the Kryptos engine.
  *
  * Represents an entity in the game world with properties such as position,
  * rotation, mass, and whether it uses gravity. Supports debug-tracked variables.
  */
class GameObject {
private:
    /**
     * @brief Stores debug-tracked variables and their associated getter functions.
     */
    std::unordered_map<std::string, std::function<std::string()>> debugTrackedValues;

protected:
    std::string name;         ///< Name of the game object.
    sf::Vector2f position;    ///< Position of the object in the game world.
    sf::Angle rotation;       ///< Rotation of the object in the game world.
    bool active;              ///< Indicates whether the object is active.
    float mass;               ///< Mass of the object, used for physics calculations.
    bool useGravity;          ///< Indicates whether the object is affected by gravity.

    /**
     * @brief Registers a variable for debugging.
     *
     * Tracks the value of a variable for display in the debug interface.
     * @tparam T The type of the variable to register.
     * @param name The name of the variable.
     * @param variable The variable to track.
     */
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
    /**
     * @brief Constructs a GameObject with specified properties.
     * @param name Name of the game object.
     * @param position Initial position of the object.
     * @param active Whether the object is active.
     * @param rotation Initial rotation of the object.
     * @param mass Mass of the object.
     * @param useGravity Whether the object is affected by gravity.
     */
    GameObject(const std::string& name,
        const sf::Vector2f& position,
        const bool& active,
        const sf::Angle& rotation,
        const float& mass,
        const bool& useGravity);

    /**
     * @brief Destructor for GameObject.
     * Unregisters the object from the GameObjectManager.
     */
    virtual ~GameObject();

    /**
     * @brief Retrieves debug-tracked variables.
     * @return A map of variable names and their getter functions.
     */
    const std::unordered_map<std::string, std::function<std::string()>>& getDebugTrackedValues() const{
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
