/**
 * @file SpriteRendererLogger.cpp
 * @brief Implements a logger specifically for the SpriteRenderer subsystem.
 *
 * @ingroup LoggingSystem
 *
 * Used to capture loading errors, warnings, and debug-level details for sprite rendering.
 * All logs are colour-coded and clearly prefixed for visibility in console output.
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../../Include/LoggingSystem/SpriteRenderer/SpriteRendererLogger.h"

namespace KryptosEngine
{
    // -----------------------------------------------------
    // Static Members
    // -----------------------------------------------------

    std::shared_ptr<spdlog::logger> SpriteRendererLogger::s_SpriteLogger;

    // -----------------------------------------------------
    // Public Static Methods
    // -----------------------------------------------------

    /**
     * @brief Initialises the Sprite Renderer logger.
     *
     * Sets up the output pattern, log level, and logger tag.
     */
    void SpriteRendererLogger::Init()
    {
        s_SpriteLogger = spdlog::stdout_color_mt("SpriteRendererLogger");
        s_SpriteLogger->set_pattern("[%T] [%^%l%$] [SpriteRenderer] %v");
        s_SpriteLogger->set_level(spdlog::level::debug);
    }

    /**
     * @brief Provides access to the Sprite Renderer logger instance.
     * @return Shared pointer to the logger.
     */
    std::shared_ptr<spdlog::logger>& SpriteRendererLogger::GetLogger()
    {
        return s_SpriteLogger;
    }

} // namespace KryptosEngine
