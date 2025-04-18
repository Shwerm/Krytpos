/**
 * @file SpriteRendererLogger.h
 * @brief Logger dedicated to the Sprite Rendering subsystem.
 *
 * @ingroup LoggingSystem
 *
 * @author
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace KryptosEngine
{
    /**
     * @class SpriteRendererLogger
     * @brief Provides logging for events and issues within the SpriteRenderer system.
     *
     * Useful for isolating rendering diagnostics from other core logs.
     */
    class SpriteRendererLogger
    {
    public:
        // -----------------------------------------------------
        // Public Static Methods
        // -----------------------------------------------------

        /**
         * @brief Initialises the Sprite Renderer logger.
         */
        static void Init();

        /**
         * @brief Gets the shared logger for Sprite Renderer.
         * @return Reference to the logger instance.
         */
        static std::shared_ptr<spdlog::logger>& GetLogger();

    private:
        // -----------------------------------------------------
        // Private Members
        // -----------------------------------------------------

        static std::shared_ptr<spdlog::logger> s_SpriteLogger; ///< Logger for sprite rendering operations.
    };
}
