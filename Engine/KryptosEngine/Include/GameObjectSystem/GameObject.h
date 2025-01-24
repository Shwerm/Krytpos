/*
Game Object Header - Krytpos - Sam Camilleri, Mural Studios
All Rights Reserved 2025.
Dependencies: string, Graphics.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameObject {
protected:
    std::string name;           // Name of the game object
    sf::Vector2f position;      // Position of the game object
    bool active;                // Whether the object is active

public:
    // Constructor
    GameObject(const std::string& name, const sf::Vector2f& position);

    // Virtual destructor
    virtual ~GameObject();

    // Pure virtual methods for update and draw
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    // Getters
    std::string getName() const;
    sf::Vector2f getPosition() const;
    bool isActive() const;

    // Setters
    void setPosition(const sf::Vector2f& newPosition);
    void setActive(bool state);
};



