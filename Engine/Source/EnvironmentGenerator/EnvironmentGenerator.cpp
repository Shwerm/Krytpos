#include "../../Include/EnvironmentGenerator/EnvironmentGenerator.h"
#include "../../Include/EnvironmentGenerator/PlatformFactory.h"
#include "../../Include/EnvironmentGenerator/RandomUtils.h"
#include "../../Include/EnemyClass/EnemyClass.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"
#include "../../Include/PlayerClass/Player.h"

#include <algorithm>

EnvironmentGenerator::EnvironmentGenerator(const TerrainGenerationSettings& settings, const sf::Vector2f& startPosition)
    : settings(settings)
{
    nextSpawnPosition = startPosition;
}

void EnvironmentGenerator::generate(Player* player) {
    // First platform (no enemy)
    const float playerHeight = 48.f;
    sf::Vector2f firstPlatformPos = nextSpawnPosition;

    std::string texturePath = settings.texturePaths[Random::Range(0, static_cast<int>(settings.texturePaths.size()))];
    auto firstPlatform = PlatformFactory::Create("StartPlatform", firstPlatformPos, texturePath);
    platforms.push_back(firstPlatform);

    // Set player respawn point slightly above first platform
    if (player) {
        sf::Vector2f respawnPoint = firstPlatformPos;
        respawnPoint.y -= playerHeight;
        player->setRespawnPosition(respawnPoint);
    }

    float firstWidth = Random::Range(settings.minPlatformWidth, settings.maxPlatformWidth);
    nextSpawnPosition.x += std::max(firstWidth, settings.minHorizontalSpacing);

    for (int i = 1; i < settings.totalPlatforms; ++i) {
        spawnPlatform();
        spawnEnemyOnPlatform(nextSpawnPosition);
    }

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
}

void EnvironmentGenerator::spawnEnemyOnPlatform(const sf::Vector2f& platformPosition) {
    if (!Random::Chance(0.5f)) return; // 50% chance

    std::string enemyTexturePath = "Assets/GameAssets/Textures/Enemies/EnemySpriteSheet.png";

    sf::Vector2f enemySpawnPos = platformPosition;
    enemySpawnPos.y -= 48.f; // Adjust based on sprite height

    auto enemy = new EnemyClass("Enemy", enemySpawnPos, enemyTexturePath);
    GameObjectManager::getInstance().registerObject(enemy);
}

void EnvironmentGenerator::spawnFinishPoint() {
    std::string texturePath = settings.texturePaths[Random::Range(0, static_cast<int>(settings.texturePaths.size()))];
    auto platform = PlatformFactory::Create("FinishPlatform", nextSpawnPosition, texturePath);

    float finishOffset = 50.0f;
    sf::Vector2f flagPosition = nextSpawnPosition + sf::Vector2f(0.f, -finishOffset);
    PlatformFactory::Create("FinishFlag", flagPosition, settings.finishPointTexturePath);

    platforms.push_back(platform);
}
