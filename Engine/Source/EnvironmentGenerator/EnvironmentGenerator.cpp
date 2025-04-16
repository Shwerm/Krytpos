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
