#include "../../Include/2DCollider/Collider2D.h"
#include <SFML/Graphics/Rect.hpp>

/**
 * @brief Constructor initializing size and offset.
 */
Collider2D::Collider2D(const sf::Vector2f& size, const sf::Vector2f& offset)
    : size(size), offset(offset), position(0.f, 0.f) {}

/**
 * @brief Sets the world-space position of the collider.
 */
void Collider2D::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

/**
 * @brief Returns the world-space bounding rectangle of the collider.
 */
sf::FloatRect Collider2D::getBounds() const {
    return sf::FloatRect(position + offset, size);
}

/**
 * @brief Sets the size of the collider.
 */
void Collider2D::setSize(const sf::Vector2f& newSize) {
    size = newSize;
}

/**
 * @brief Returns the current size of the collider.
 */
sf::Vector2f Collider2D::getSize() const {
    return size;
}

/**
 * @brief Determines whether two Collider2D instances intersect.
 */
bool Collider2D::intersects(const Collider2D& a, const Collider2D& b) {
    const auto rectA = a.getBounds();
    const auto rectB = b.getBounds();

    return (
        rectA.position.x < rectB.position.x + rectB.size.x &&
        rectA.position.x + rectA.size.x > rectB.position.x &&
        rectA.position.y < rectB.position.y + rectB.size.y &&
        rectA.position.y + rectA.size.y > rectB.position.y
        );
}

/**
 * @brief Renders the collider as a red wireframe rectangle for debugging purposes.
 */
void Collider2D::drawDebug(sf::RenderWindow& window) const {
    sf::RectangleShape rect;
    rect.setSize(size);
    rect.setPosition(position + offset);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Red);
    rect.setOutlineThickness(1.f);
    window.draw(rect);
}
