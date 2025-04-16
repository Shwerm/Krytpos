// EnvironmentGenerator.hpp

#pragma once
#include "../EnvironmentGenerator/TerrainGenerationSettings.h"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <memory>

class Platform;

class EnvironmentGenerator {
public:
    EnvironmentGenerator(const TerrainGenerationSettings& settings, const sf::Vector2f& startPosition);

    void generate();

private:
    void spawnPlatform();
    void spawnEnemyOnPlatform(const sf::Vector2f& platformPosition); 
    void spawnFinishPoint();

    const TerrainGenerationSettings& settings;
    sf::Vector2f nextSpawnPosition;
    std::vector<std::shared_ptr<Platform>> platforms;
};
