// EnvironmentGenerator.cpp

#include "../../Include/EnvironmentGenerator/EnvironmentGenerator.h"
#include "../../Include/EnvironmentGenerator/PlatformFactory.h"
#include "../../Include/EnvironmentGenerator/RandomUtils.h"
#include <algorithm>

EnvironmentGenerator::EnvironmentGenerator(const TerrainGenerationSettings& settings, const sf::Vector2f& startPosition)
    : settings(settings)
{
    float firstWidth = Random::Range(settings.minPlatformWidth, settings.maxPlatformWidth);
    nextSpawnPosition = startPosition + sf::Vector2f(firstWidth, 0.f);
}

void EnvironmentGenerator::generate() {
    for (int i = 0; i < settings.totalPlatforms; ++i)
        spawnPlatform();

    spawnFinishPoint();
}

void EnvironmentGenerator::spawnPlatform() {
    // Define platform properties
    float platformWidth = Random::Range(settings.minPlatformWidth, settings.maxPlatformWidth);
    std::string texturePath = settings.texturePaths[Random::Range(0, settings.texturePaths.size())];

    // Start from next spawn position
    sf::Vector2f spawnPos = nextSpawnPosition;
    bool vertical = Random::Chance(settings.verticalStackChance);

    if (vertical) {
        float yOffset = Random::Range(-settings.sameXOffsetYRange, settings.sameXOffsetYRange);
        spawnPos.y = std::clamp(spawnPos.y + yOffset, settings.minY, settings.maxY);
        spawnPos.x += Random::Range(settings.minPlatformWidth * 0.5f, settings.minPlatformWidth); // X spacing even for vertical
    }
    else {
        float yOffset = Random::Range(-settings.heightVariance, settings.heightVariance);
        spawnPos.y = std::clamp(spawnPos.y + yOffset, settings.minY, settings.maxY);
        spawnPos.x += platformWidth;
    }

    auto platform = PlatformFactory::Create("Platform", spawnPos, texturePath);
    platforms.push_back(platform);

    // Update for next spawn
    nextSpawnPosition = spawnPos;
}


void EnvironmentGenerator::spawnFinishPoint() {
    std::string texturePath = settings.texturePaths[Random::Range(0, settings.texturePaths.size())];
    auto platform = PlatformFactory::Create("FinishPlatform", nextSpawnPosition, texturePath);

    float finishOffset = 50.0f; // arbitrary Y offset for flag, customisable
    sf::Vector2f flagPosition = nextSpawnPosition + sf::Vector2f(0.f, -finishOffset);
    PlatformFactory::Create("FinishFlag", flagPosition, settings.finishPointTexturePath);

    platforms.push_back(platform);
}
