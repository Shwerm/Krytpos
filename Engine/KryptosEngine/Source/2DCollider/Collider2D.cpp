// Collider2D.cpp

#include "../../Include/2DCollider/Collider2D.h"

Collider2D::Collider2D(const sf::Vector2f& size, const sf::Vector2f& offset)
    : size(size), offset(offset), position(0.f, 0.f) {}

void Collider2D::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

sf::FloatRect Collider2D::getBounds() const {
    return sf::FloatRect(position + offset, size);
}

void Collider2D::setSize(const sf::Vector2f& newSize) {
    size = newSize;
}

sf::Vector2f Collider2D::getSize() const {
    return size;
}
