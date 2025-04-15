// RandomUtils.hpp

#pragma once
#include <random>

namespace Random {
    inline float Range(float min, float max) {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rng);
    }

    inline int Range(int min, int max) {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(min, max - 1);
        return dist(rng);
    }

    inline bool Chance(float probability) {
        return Range(0.f, 1.f) < probability;
    }
}
