// EnvironmentGenerator.cpp

#include "../../Include/EnvironmentGenerator/EnvironmentGenerator.h"
#include "../../Include/EnvironmentGenerator/PlatformFactory.h"
#include "../../Include/EnvironmentGenerator/RandomUtils.h"
#include "../../Include/EnemyClass/EnemyClass.h"
#include <algorithm>

EnvironmentGenerator::EnvironmentGenerator(const TerrainGenerationSettings& settings, const sf::Vector2f& startPosition)
    : settings(settings)
{
    nextSpawnPosition = startPosition;
}

void EnvironmentGenerator::generate() {
    // Correct Y-offset to place platform under the player
    const float playerHeight = 48.f; // Match collider height
    sf::Vector2f firstPlatformPos = nextSpawnPosition; // Already aligned by main.cpp

    std::string texturePath = settings.texturePaths[Random::Range(0, static_cast<int>(settings.texturePaths.size()))];
    auto firstPlatform = PlatformFactory::Create("StartPlatform", firstPlatformPos, texturePath);
    platforms.push_back(firstPlatform);

    // Offset for next generation
    float firstWidth = Random::Range(settings.minPlatformWidth, settings.maxPlatformWidth);
    nextSpawnPosition.x += std::max(firstWidth, settings.minHorizontalSpacing);

    for (int i = 1; i < settings.totalPlatforms; ++i)
        spawnPlatform();

    spawnFinishPoint();
}

void EnvironmentGenerator::spawnPlatform() {
    float platformWidth = Random::Range(settings.minPlatformWidth, settings.maxPlatformWidth);
    std::string texturePath = settings.texturePaths[Random::Range(0, static_cast<int>(settings.texturePaths.size()))];

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

    // ---- New Enemy Spawn Logic ----
    if (Random::Chance(0.5f)) {
        if (platform->hasCollider()) {
            ::sf::FloatRect bounds = platform->getCollider()->getBounds();
            float margin = 20.f;

            float patrolLeft = bounds.left + margin;
            float patrolRight = bounds.left + bounds.width - margin;

            sf::Vector2f enemySpawn = {
                (patrolLeft + patrolRight) / 2.f,
                bounds.top - 48.f // enemy stands just above the platform
            };

            auto enemy = new EnemyClass("Enemy", enemySpawn, patrolLeft, patrolRight);
            enemy->setUseGravity(true);
        }
    }
}

void EnvironmentGenerator::spawnFinishPoint() {
    std::string texturePath = settings.texturePaths[Random::Range(0, static_cast<int>(settings.texturePaths.size()))];
    auto platform = PlatformFactory::Create("FinishPlatform", nextSpawnPosition, texturePath);

    float finishOffset = 50.0f;
    sf::Vector2f flagPosition = nextSpawnPosition + sf::Vector2f(0.f, -finishOffset);
    PlatformFactory::Create("FinishFlag", flagPosition, settings.finishPointTexturePath);

    platforms.push_back(platform);
}
