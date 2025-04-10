// TerrainGenerationSettings.hpp

#pragma once
#include <string>
#include <vector>

struct TerrainGenerationSettings {
    int totalPlatforms = 20;

    float minPlatformWidth = 200.0f;
    float maxPlatformWidth = 400.0f;

    float verticalStackChance = 0.25f;
    float heightVariance = 30.0f;
    float sameXOffsetYRange = 60.0f;
    float minY = 150.0f;
    float maxY = 500.0f;

    std::vector<std::string> texturePaths; // texture path for variety
    std::string finishPointTexturePath;
};
