/**
 * @file EnvironmentGenerator.cpp
 * @brief Implementation of the EnvironmentGenerator class for procedural level generation.
 *
 * @ingroup EnvironmentSystem
 *
 * Spawns platforms, enemies, and finish points along a generated path based on configurable settings.
 * Supports both vertical and horizontal stacking behaviour with randomised offsets.
 *
 * This generator is used during initialisation to build the level before play begins.
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/EnvironmentGenerator/EnvironmentGenerator.h"
#include "../../Include/EnvironmentGenerator/PlatformFactory.h"
#include "../../Include/EnvironmentGenerator/RandomUtils.h"
#include "../../Include/EnemyClass/EnemyClass.h"
#include "../../Include/GameObjectSystem/GameObjectManager.h"
#include "../../Include/PlayerClass/Player.h"

#include <algorithm>

 // -----------------------------------------------------
 // Constructor
 // -----------------------------------------------------

 /**
  * @brief Constructs a new EnvironmentGenerator using generation settings and a starting position.
  * @param settings Reference to TerrainGenerationSettings data.
  * @param startPosition World-space position to begin spawning platforms.
  */
EnvironmentGenerator::EnvironmentGenerator(const TerrainGenerationSettings& settings, const sf::Vector2f& startPosition)
    : settings(settings)
{
    nextSpawnPosition = startPosition;
}

// -----------------------------------------------------
// Public Methods
// -----------------------------------------------------

/**
 * @brief Begins terrain and platform generation.
 * Spawns the initial platform, all intermediate platforms, and the final goal area.
 * @param player Optional pointer to player for setting initial respawn location.
 */
void EnvironmentGenerator::generate(Player* player)
{
    const float playerHeight = 48.f;

    // First platform spawn
    sf::Vector2f firstPlatformPos = nextSpawnPosition;
    std::string texturePath = settings.texturePaths[Random::Range(0, static_cast<int>(settings.texturePaths.size()))];
    auto firstPlatform = PlatformFactory::Create("StartPlatform", firstPlatformPos, texturePath);
    platforms.push_back(firstPlatform);

    // Set player spawn point above first platform
    if (player) {
        sf::Vector2f respawnPoint = firstPlatformPos;
        respawnPoint.y -= playerHeight;
        player->setRespawnPosition(respawnPoint);
    }

    // Advance horizontally
    float firstWidth = Random::Range(settings.minPlatformWidth, settings.maxPlatformWidth);
    nextSpawnPosition.x += std::max(firstWidth, settings.minHorizontalSpacing);

    // Generate the full platform sequence
    for (int i = 1; i < settings.totalPlatforms; ++i) {
        spawnPlatform();
        spawnEnemyOnPlatform(nextSpawnPosition);
    }

    // Place finish line/platform
    spawnFinishPoint();
}

// -----------------------------------------------------
// Private Methods
// -----------------------------------------------------

/**
 * @brief Spawns a single platform at the next calculated position and advances spawn position.
 */
void EnvironmentGenerator::spawnPlatform()
{
    float platformWidth = Random::Range(settings.minPlatformWidth, settings.maxPlatformWidth);
    std::string texturePath = settings.texturePaths[Random::Range(0, static_cast<int>(settings.texturePaths.size()))];

    sf::Vector2f spawnPos = nextSpawnPosition;
    bool vertical = Random::Chance(settings.verticalStackChance);

    // Vertical offset
    float yOffset = vertical
        ? Random::Range(-settings.sameXOffsetYRange, settings.sameXOffsetYRange)
        : Random::Range(-settings.heightVariance, settings.heightVariance);

    spawnPos.y = std::clamp(spawnPos.y + yOffset, settings.minY, settings.maxY);

    // Horizontal advance logic
    float horizontalStep = vertical ? platformWidth * 0.5f : platformWidth;
    horizontalStep = std::max(horizontalStep, settings.minHorizontalSpacing);
    spawnPos.x += horizontalStep;

    // Spawn and store the platform
    auto platform = PlatformFactory::Create("Platform", spawnPos, texturePath);
    platforms.push_back(platform);

    // Update for next spawn
    nextSpawnPosition = spawnPos;
}

/**
 * @brief Conditionally spawns an enemy on the current platform.
 * @param platformPosition Position of the platform the enemy should stand on.
 */
void EnvironmentGenerator::spawnEnemyOnPlatform(const sf::Vector2f& platformPosition)
{
    if (!Random::Chance(0.5f)) return;

    std::string enemyTexturePath = "Assets/GameAssets/Textures/Enemies/EnemySpriteSheet.png";

    sf::Vector2f enemySpawnPos = platformPosition;
    enemySpawnPos.y -= 48.f; // Height adjustment based on sprite

    auto enemy = new EnemyClass("Enemy", enemySpawnPos, enemyTexturePath);
    GameObjectManager::getInstance().registerObject(enemy);
}

/**
 * @brief Spawns the finish platform and decorative flag at the end of the generated environment.
 */
void EnvironmentGenerator::spawnFinishPoint()
{
    std::string texturePath = settings.texturePaths[Random::Range(0, static_cast<int>(settings.texturePaths.size()))];
    auto platform = PlatformFactory::Create("FinishPlatform", nextSpawnPosition, texturePath);

    float finishOffset = 50.0f;
    sf::Vector2f flagPosition = nextSpawnPosition + sf::Vector2f(0.f, -finishOffset);
    PlatformFactory::Create("FinishFlag", flagPosition, settings.finishPointTexturePath);

    platforms.push_back(platform);
}
