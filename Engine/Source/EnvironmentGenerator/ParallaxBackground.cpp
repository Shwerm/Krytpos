#include "../../Include/EnvironmentGenerator/ParallaxBackground.h"

ParallaxBackground::ParallaxBackground(float windowWidth)
{
    // Sky background - static in X, moves with camera in Y
    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-bg.png",
        0.0f, windowWidth, 4.0f, 0.0f, -2076.0f, false, true));

    // Scrollable, repeatable parallax layers
    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-montain-far.png",
        0.25f, windowWidth, 4.0f, 100.0f, -420.0f));

    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-mountains.png",
        0.4f, windowWidth, 4.0f, 300.0f, -420.f));

    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-trees.png",
        0.6f, windowWidth, 4.0f, 360.0f, -420.0f));

    layers.emplace_back(std::make_unique<ParallaxLayer>(
        "Assets/GameAssets/Textures/Environment/ParallaxBackground/parallax-mountain-foreground-trees.png",
        0.8f, windowWidth, 4.0f, 360.0f, -420.0f));
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
