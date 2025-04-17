#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

/**
 * @brief Represents a single layer in the parallax background.
 */
class ParallaxLayer
{
public:
    ParallaxLayer(const std::string& texturePath, float scrollSpeed, float windowWidth, float scale, float yOffset);
    ~ParallaxLayer() = default;

    void update(float cameraX, const sf::View& cameraView);
    void draw(sf::RenderTarget& target);

private:
    sf::Texture texture;
    std::unique_ptr<sf::Sprite> sprite1;
    std::unique_ptr<sf::Sprite> sprite2;

    float speed;
    float width;
    float scale;
    float yOffset;

    void wrapSprites(float cameraX);
};
