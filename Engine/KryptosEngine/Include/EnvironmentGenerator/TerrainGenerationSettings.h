// TerrainGenerationSettings.hpp

#pragma once
#include <string>
#include <vector>

struct TerrainGenerationSettings {
    int totalPlatforms = 10;

    float minPlatformWidth = 1.0f;
    float maxPlatformWidth = 3.0f;

    float verticalStackChance = 0.25f;
    float heightVariance = 1.0f;
    float sameXOffsetYRange = 1.0f;
    float minY = -3.0f;
    float maxY = 3.0f;

    std::vector<std::string> texturePaths; // texture path for variety
};
