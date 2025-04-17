#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <optional>

/**
 * @brief Represents a single layer in the parallax background.
 */
class ParallaxLayer
{
public:
    ParallaxLayer(const std::string& texturePath, float scrollSpeed, float windowWidth);

    void update(float cameraX);
    void draw(sf::RenderTarget& target);

private:
    sf::Texture texture;
    std::optional<sf::Sprite> sprite1;
    std::optional<sf::Sprite> sprite2;

    float speed;
    float width;

    void wrapSprites(float cameraX);
};
