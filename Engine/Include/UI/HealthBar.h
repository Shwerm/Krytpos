#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief UI HealthBar component to display player's health.
 */
class HealthBar {
public:
    HealthBar(const sf::Vector2f& position, const sf::Vector2f& size);

    void setTextures(const sf::Texture& backgroundTexture, const sf::Texture& fillTexture);
    void setHealth(float current, float max);
    void draw(sf::RenderTarget& target) const;

private:
    sf::Sprite backgroundSprite;
    sf::Sprite fillSprite;

    sf::Vector2f size;
    float currentHealth;
    float maxHealth;
};
