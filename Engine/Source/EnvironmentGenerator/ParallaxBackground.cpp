#include "../../Include/EnvironmentGenerator/ParallaxBackground.h"

ParallaxBackground::ParallaxBackground(float windowWidth)
{
    layers.emplace_back("Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-bg.png", 0.1f, windowWidth);
    layers.emplace_back("Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-montain-far.png", 0.25f, windowWidth);
    layers.emplace_back("Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-mountains.png", 0.4f, windowWidth);
    layers.emplace_back("Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-trees.png", 0.6f, windowWidth);
    layers.emplace_back("Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-foreground-trees.png", 0.8f, windowWidth);
}

void ParallaxBackground::update(float cameraX)
{
    for (auto& layer : layers)
        layer.update(cameraX);
}

void ParallaxBackground::draw(sf::RenderTarget& target)
{
    for (auto& layer : layers)
        layer.draw(target);
}
