/*
Game Object Header - Krytpos - Sam Camilleri, Mural Studios
Dependencies: string, Graphics.hpp
*/

#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include <SFML/Graphics.hpp>

class GameObject {
protected:
    std::string name;           // Name of the game object
    sf::Vector2f position;      // Position of the game object
    sf::Angle rotation;         // Rotation of the game object
    bool active;                // Whether the object is active or not

public:
    // Constructor with default values
    GameObject(const std::string& name = "NullObject", const sf::Vector2f& position = sf::Vector2f(0.f, 0.f));

    // Virtual destructor to allow proper cleanup of derived classes
    virtual ~GameObject() = default;

    // Pure virtual methods for update and draw
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    // Getters and setters
    void setPosition(const sf::Vector2f& newPosition);
    sf::Vector2f getPosition() const;

    const std::string& getName() const { return name; }

    bool isActive() const;
    void setActive(bool state);
};

#endif // GAMEOBJECT_H


