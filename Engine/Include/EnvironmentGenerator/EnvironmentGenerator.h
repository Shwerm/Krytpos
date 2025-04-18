/**
 * @file EnvironmentGenerator.h
 * @brief Procedural environment generation manager for spawning platforms, enemies, and level progression.
 *
 * @ingroup EnvironmentSystem
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include "../EnvironmentGenerator/TerrainGenerationSettings.h"
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <memory>

class Platform;
class Player;

/**
 * @class EnvironmentGenerator
 * @brief Handles procedural spawning of platforms and related gameplay elements during runtime.
 *
 * Operates based on terrain settings and the player’s progression to extend the environment.
 */
class EnvironmentGenerator
{
public:
    // -----------------------------------------------------
    // Constructors / Destructor
    // -----------------------------------------------------

    /**
     * @brief Constructs the environment generator with generation settings and a start position.
     * @param settings Configuration settings for terrain generation.
     * @param startPosition World-space position to begin generating.
     */
    EnvironmentGenerator(const TerrainGenerationSettings& settings, const sf::Vector2f& startPosition);

    // -----------------------------------------------------
    // Public Methods
    // -----------------------------------------------------

    /**
     * @brief Spawns new environment elements relative to the player's position.
     * @param player Pointer to the active player.
     */
    void generate(Player* player);

private:
    // -----------------------------------------------------
    // Private Methods
    // -----------------------------------------------------

    /**
     * @brief Spawns a single platform at the next spawn position.
     */
    void spawnPlatform();

    /**
     * @brief Spawns an enemy positioned relative to the given platform.
     * @param platformPosition World-space position of the target platform.
     */
    void spawnEnemyOnPlatform(const sf::Vector2f& platformPosition);

    /**
     * @brief Spawns the final objective or endpoint for the level.
     */
    void spawnFinishPoint();

    // -----------------------------------------------------
    // Private Members
    // -----------------------------------------------------

    const TerrainGenerationSettings& settings; ///< Settings used to control terrain spawning rules.
    sf::Vector2f nextSpawnPosition;            ///< Next world position for platform spawning.
    std::vector<std::shared_ptr<Platform>> platforms; ///< List of all active platform instances.
};
