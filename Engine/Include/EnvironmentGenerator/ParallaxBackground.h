#pragma once

#include <vector>
#include <memory>
#include "ParallaxLayer.h"

/**
 * @brief Handles and draws all parallax layers in the correct order.
 */
class ParallaxBackground
{
public:
    ParallaxBackground(float windowWidth);

    void update(float cameraX);
    void draw(sf::RenderTarget& target);

private:
    std::vector<std::unique_ptr<ParallaxLayer>> layers;
};
