/**
 * @file Collider2D.h
 * @brief 2D Axis-Aligned Bounding Box Collider for the Physics System.
 *
 * @ingroup PhysicsSystem
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include <SFML/Graphics.hpp>

 /**
  * @class Collider2D
  * @brief Represents a 2D axis-aligned bounding box collider used for collision detection.
  *
  * Provides simple AABB collision checking, transformation, and optional debug rendering.
  */
class Collider2D
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs a Collider2D with a specified size and optional offset.
     * @param size Width and height of the collider.
     * @param offset Optional local offset from the object's position.
     */
    Collider2D(const sf::Vector2f& size, const sf::Vector2f& offset = { 0.f, 0.f });

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    /**
     * @brief Sets the world position of the collider.
     * @param pos New world-space position.
     */
    void setPosition(const sf::Vector2f& pos);

    /**
     * @brief Retrieves the collider's world-space bounding rectangle.
     * @return A FloatRect representing the collider bounds.
     */
    sf::FloatRect getBounds() const;

    /**
     * @brief Updates the collider's size.
     * @param size New width and height values.
     */
    void setSize(const sf::Vector2f& size);

    /**
     * @brief Renders the collider visually for debugging purposes.
     * @param window Render window for drawing.
     */
    void drawDebug(sf::RenderWindow& window) const;

    /**
     * @brief Performs an intersection test between two Collider2D objects.
     * @param a First collider.
     * @param b Second collider.
     * @return True if their bounds intersect.
     */
    static bool intersects(const Collider2D& a, const Collider2D& b);

    // -----------------------------------------------------
    // Getters
    // -----------------------------------------------------

    /**
     * @brief Gets the current size of the collider.
     * @return Vector2f containing width and height.
     */
    sf::Vector2f getSize() const;

    /**
     * @brief Gets the local offset applied to the collider.
     * @return Offset as a Vector2f.
     */
    sf::Vector2f getOffset() const;

private:
    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    sf::Vector2f size;     ///< Width and height of the collider.
    sf::Vector2f offset;   ///< Local offset from the object's position.
    sf::Vector2f position; ///< World-space position of the collider.
};
