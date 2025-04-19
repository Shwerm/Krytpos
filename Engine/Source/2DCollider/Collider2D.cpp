/**
 * @file Collider2D.cpp
 * @brief Implementation of the Collider2D class for axis-aligned bounding box collisions.
 *
 * @ingroup PhysicsSystem
 *
 * Handles collision bounds, position setting, debug drawing, and static intersection testing.
 * Used primarily for 2D platformer physics in the Kryptos Engine.
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/2DCollider/Collider2D.h"
#include <SFML/Graphics/Rect.hpp>

 // -----------------------------------------------------
 // Constructor
 // -----------------------------------------------------

 /**
  * @brief Constructs a Collider2D with a given size and optional offset.
  * @param size Dimensions of the collider (width and height).
  * @param offset Local offset from the owning GameObject's origin.
  */
Collider2D::Collider2D(const sf::Vector2f& size, const sf::Vector2f& offset)
    : size(size), offset(offset), position(0.f, 0.f) {}

// -----------------------------------------------------
// Public Methods
// -----------------------------------------------------

/**
 * @brief Sets the world-space position of the collider.
 * @param pos World-space position of the owning GameObject.
 */
void Collider2D::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

/**
 * @brief Retrieves the bounding rectangle of this collider in world space.
 * @return FloatRect defining the position and size of the collider.
 */
sf::FloatRect Collider2D::getBounds() const {
    return sf::FloatRect(position + offset, size);
}

/**
 * @brief Sets the collider’s size (width and height).
 * @param newSize New size to apply to the collider.
 */
void Collider2D::setSize(const sf::Vector2f& newSize) {
    size = newSize;
}

/**
 * @brief Retrieves the current collider size.
 * @return A vector representing the width and height of the collider.
 */
sf::Vector2f Collider2D::getSize() const {
    return size;
}

/**
 * @brief Draws the collider bounds as a red wireframe rectangle for debugging purposes.
 * @param window Reference to the SFML render window.
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

// -----------------------------------------------------
// Static Methods
// -----------------------------------------------------

/**
 * @brief Determines whether two colliders intersect using AABB logic.
 * @param a First collider.
 * @param b Second collider.
 * @return True if they intersect, false otherwise.
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
