#include "../../Include/EnvironmentGenerator/ParallaxBackground.h"

ParallaxBackground::ParallaxBackground(float windowWidth)
{
    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-bg.png", 0.1f, windowWidth, 3.0f, 280.0f));

    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-montain-far.png", 0.25f, windowWidth, 3.0f, 260.0f));

    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-mountains.png", 0.4f, windowWidth, 3.0f, 240.0f));

    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-trees.png", 0.6f, windowWidth, 3.0f, 220.0f));

    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-foreground-trees.png", 0.8f, windowWidth, 3.0f, 200.0f));
}

void ParallaxBackground::update(float cameraX, const sf::View& cameraView)
{
    for (auto& layer : layers)
        layer->update(cameraX, cameraView);
}

void ParallaxBackground::draw(sf::RenderTarget& target)
{
    for (auto& layer : layers)
        layer->draw(target);
}
