/*
Game Object Header - Krytpos - Sam Camilleri, Mural Studios
All Rights Reserved 2025.
Dependencies: string, Graphics.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameObject {
	// Protected members are accessible by derived classes
    // GameObject values
protected:
    std::string name;      
    sf::Vector2f position;
	sf::Angle rotation;
    bool active;       
    float mass;
	bool useGravity;

public:
    // Constructor
    GameObject(const std::string& name, const sf::Vector2f& position, const sf::Angle& rotation, const float& mass, const bool& useGravity);

    // Virtual destructor
    virtual ~GameObject();

    // Pure virtual methods for update and draw
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

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



