// EnvironmentGenerator.cpp

#include "../../Include/EnvironmentGenerator/EnvironmentGenerator.h"
#include "../../Include/EnvironmentGenerator/PlatformFactory.h"
#include "../../Include/EnvironmentGenerator/RandomUtils.h"
#include <algorithm>

EnvironmentGenerator::EnvironmentGenerator(const TerrainGenerationSettings& settings, const sf::Vector2f& startPosition)
    : settings(settings)
{
    // First platform will be manually placed under the player, so just store startPosition
    nextSpawnPosition = startPosition;
}

void EnvironmentGenerator::generate() {
    // Spawn first platform directly under the player
    std::string texturePath = settings.texturePaths[Random::Range(0, settings.texturePaths.size())];

    auto firstPlatform = PlatformFactory::Create("StartPlatform", nextSpawnPosition, texturePath);
    platforms.push_back(firstPlatform);

    // Offset spawn position for remaining platforms
    float firstWidth = Random::Range(settings.minPlatformWidth, settings.maxPlatformWidth);
    nextSpawnPosition.x += std::max(firstWidth, settings.minHorizontalSpacing);

    // Generate remaining platforms
    for (int i = 1; i < settings.totalPlatforms; ++i)
        spawnPlatform();

    spawnFinishPoint();
}

void EnvironmentGenerator::spawnPlatform() {
    float platformWidth = Random::Range(settings.minPlatformWidth, settings.maxPlatformWidth);
    std::string texturePath = settings.texturePaths[Random::Range(0, settings.texturePaths.size())];

    sf::Vector2f spawnPos = nextSpawnPosition;
    bool vertical = Random::Chance(settings.verticalStackChance);

    float yOffset = vertical
        ? Random::Range(-settings.sameXOffsetYRange, settings.sameXOffsetYRange)
        : Random::Range(-settings.heightVariance, settings.heightVariance);

    spawnPos.y = std::clamp(spawnPos.y + yOffset, settings.minY, settings.maxY);

    float horizontalStep = vertical ? platformWidth * 0.5f : platformWidth;
    horizontalStep = std::max(horizontalStep, settings.minHorizontalSpacing);
    spawnPos.x += horizontalStep;

    auto platform = PlatformFactory::Create("Platform", spawnPos, texturePath);
    platforms.push_back(platform);

    nextSpawnPosition = spawnPos;
}

void EnvironmentGenerator::spawnFinishPoint() {
    std::string texturePath = settings.texturePaths[Random::Range(0, settings.texturePaths.size())];
    auto platform = PlatformFactory::Create("FinishPlatform", nextSpawnPosition, texturePath);

    float finishOffset = 50.0f;
    sf::Vector2f flagPosition = nextSpawnPosition + sf::Vector2f(0.f, -finishOffset);
    PlatformFactory::Create("FinishFlag", flagPosition, settings.finishPointTexturePath);

    platforms.push_back(platform);
}
