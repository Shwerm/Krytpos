// Collider2D.h

#pragma once
#include <SFML/Graphics.hpp>

class Collider2D {
public:
    Collider2D(const sf::Vector2f& size, const sf::Vector2f& offset = { 0.f, 0.f });

    void setPosition(const sf::Vector2f& pos);
    sf::FloatRect getBounds() const;
    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const;

    void drawDebug(sf::RenderWindow& window) const;

    static bool intersects(const Collider2D& a, const Collider2D& b);

private:
    sf::Vector2f size;
    sf::Vector2f offset;
    sf::Vector2f position;
};
