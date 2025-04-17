// Collider2D.h

#pragma once
#include <SFML/Graphics.hpp>

/**
 * @class Collider2D
 * @brief Represents a 2D axis-aligned bounding box collider used for collision detection.
 *
 * This class provides simple AABB collision functionality and optional debug rendering.
 */
class Collider2D {
public:
    /**
     * @brief Constructs a Collider2D with a specified size and optional offset.
     * @param size The size of the collider (width and height).
     * @param offset The local offset from the object's position. Default is (0, 0).
     */
    Collider2D(const sf::Vector2f& size, const sf::Vector2f& offset = { 0.f, 0.f });

    /**
     * @brief Sets the world position of the collider.
     * @param pos The new position.
     */
    void setPosition(const sf::Vector2f& pos);

    /**
     * @brief Retrieves the collider's world-space bounding rectangle.
     * @return sf::FloatRect representing the bounds.
     */
    sf::FloatRect getBounds() const;

    /**
     * @brief Updates the size of the collider.
     * @param size New size (width and height).
     */
    void setSize(const sf::Vector2f& size);

    /**
     * @brief Returns the current size of the collider.
     * @return sf::Vector2f representing width and height.
     */
    sf::Vector2f getSize() const;

    /**
     * @brief Renders a visual representation of the collider for debugging.
     * @param window Reference to the render window.
     */
    void drawDebug(sf::RenderWindow& window) const;

    /**
     * @brief Checks if two colliders intersect.
     * @param a First collider.
     * @param b Second collider.
     * @return True if the colliders overlap, false otherwise.
     */
    static bool intersects(const Collider2D& a, const Collider2D& b);

    /**
     * @brief Returns the local offset of the collider from the object's position.
     * @return sf::Vector2f offset.
     */
    sf::Vector2f getOffset() const { return offset; }


private:
    sf::Vector2f size;     ///< Width and height of the collider.
    sf::Vector2f offset;   ///< Local offset from the object's position.
    sf::Vector2f position; ///< World-space position of the collider.
};
