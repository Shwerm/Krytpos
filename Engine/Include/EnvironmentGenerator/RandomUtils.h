/**
 * @file RandomUtils.h
 * @brief Utility functions for generating random numbers and probabilities.
 *
 * @ingroup UtilitySystem
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include <random>

 /**
  * @namespace Random
  * @brief Provides convenient access to random number generation for gameplay systems.
  */
namespace Random
{
    /**
     * @brief Returns a random float within the given range [min, max).
     * @param min Minimum value (inclusive).
     * @param max Maximum value (exclusive).
     * @return Random float within the range.
     */
    inline float Range(float min, float max)
    {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<float> dist(min, max);
        return dist(rng);
    }

    /**
     * @brief Returns a random integer within the given range [min, max).
     * @param min Minimum value (inclusive).
     * @param max Maximum value (exclusive).
     * @return Random integer within the range.
     */
    inline int Range(int min, int max)
    {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(min, max - 1);
        return dist(rng);
    }

    /**
     * @brief Returns true with the given probability.
     * @param probability Float between 0.0 and 1.0 representing the chance.
     * @return True with the given probability, false otherwise.
     */
    inline bool Chance(float probability)
    {
        return Range(0.f, 1.f) < probability;
    }
}
