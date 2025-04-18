/**
 * @file PlatformFactory.h
 * @brief Static factory for spawning platform objects during runtime.
 *
 * @ingroup EnvironmentSystem
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include "../EnvironmentGenerator/Platform.h"
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <string>

 /**
  * @class PlatformFactory
  * @brief Provides a convenient static interface for creating Platform instances.
  *
  * Typically used during procedural environment generation.
  */
class PlatformFactory
{
public:
    // -----------------------------------------------------
    // Static Methods
    // -----------------------------------------------------

    /**
     * @brief Creates a new shared pointer instance of a Platform.
     * @param name Unique platform identifier.
     * @param position World-space spawn position.
     * @param texturePath Path to the texture for rendering the platform.
     * @return Shared pointer to a new Platform object.
     */
    static std::shared_ptr<Platform> Create(const std::string& name,
        const sf::Vector2f& position,
        const std::string& texturePath);
};
