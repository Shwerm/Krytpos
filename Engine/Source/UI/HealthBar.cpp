#include "../../Include/UI/HealthBar.h"

/**
 * @brief Construct a new HealthBar object at a given position and size.
 */
HealthBar::HealthBar(const sf::Vector2f& position, const sf::Vector2f& size)
    : size(size), currentHealth(100.0f), maxHealth(100.0f)
{
    backgroundSprite.setPosition(position);
    fillSprite.setPosition(position);
}

/**
 * @brief Set the background and fill textures for the health bar.
 */
void HealthBar::setTextures(const sf::Texture& backgroundTexture, const sf::Texture& fillTexture)
{
    backgroundSprite.setTexture(backgroundTexture);
    fillSprite.setTexture(fillTexture);
}

/**
 * @brief Set the current and max health to control the fill amount.
 */
void HealthBar::setHealth(float current, float max)
{
    currentHealth = current;
    maxHealth = max;

    float healthPercent = (maxHealth > 0.0f) ? (currentHealth / maxHealth) : 0.0f;

    // Scale the fill bar width according to health percentage
    auto originalSize = fillSprite.getTexture()->getSize();
    fillSprite.setTextureRect({
        { 0, 0 },
        { static_cast<int>(originalSize.x * healthPercent), static_cast<int>(originalSize.y) }
        });
}

/**
 * @brief Draw the health bar to the target render surface.
 */
void HealthBar::draw(sf::RenderTarget& target) const
{
    target.draw(backgroundSprite);
    target.draw(fillSprite);
}
