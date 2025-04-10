// Collider2D.cpp

#include "../../Include/2DCollider/Collider2D.h"

Collider2D::Collider2D(const sf::Vector2f& size, const sf::Vector2f& offset)
    : size(size), offset(offset), position(0.f, 0.f) {}

void Collider2D::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

sf::Rect<float> Collider2D::getBounds() const {
    return sf::Rect<float>(position + offset, size);
}

void Collider2D::setSize(const sf::Vector2f& newSize) {
    size = newSize;
}

sf::Vector2f Collider2D::getSize() const {
    return size;
}

bool Collider2D::intersects(const Collider2D& a, const Collider2D& b) {
    const auto rectA = a.getBounds();
    const auto rectB = b.getBounds();

    return (
        rectA.left < rectB.left + rectB.width &&
        rectA.left + rectA.width > rectB.left &&
        rectA.top < rectB.top + rectB.height &&
        rectA.top + rectA.height > rectB.top
        );
}

