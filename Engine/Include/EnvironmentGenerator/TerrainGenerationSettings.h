/**
 * @file TerrainGenerationSettings.h
 * @brief Settings struct used to define procedural generation rules for platforms and terrain.
 *
 * @ingroup EnvironmentSystem
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include <string>
#include <vector>

 /**
  * @struct TerrainGenerationSettings
  * @brief Contains adjustable values used by EnvironmentGenerator for procedural terrain generation.
  */
struct TerrainGenerationSettings
{
    int totalPlatforms = 20; ///< Total number of platforms to generate.

    float minPlatformWidth = 200.0f; ///< Minimum width of each platform.
    float maxPlatformWidth = 400.0f; ///< Maximum width of each platform.
    float minHorizontalSpacing = 100.0f; ///< Minimum X-axis distance between platforms.

    float verticalStackChance = 0.25f; ///< Probability that a platform spawns above the previous one.
    float heightVariance = 30.0f; ///< Random Y-offset for vertical platform placement.
    float sameXOffsetYRange = 60.0f; ///< Vertical range for stacking on same X position.
    float minY = 150.0f; ///< Minimum Y position for platform generation.
    float maxY = 500.0f; ///< Maximum Y position for platform generation.

    std::vector<std::string> texturePaths; ///< List of textures to randomly assign to platforms.
    std::string finishPointTexturePath; ///< Texture for the final goal platform.
};
