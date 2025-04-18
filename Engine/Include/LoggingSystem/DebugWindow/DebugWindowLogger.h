/**
 * @file DebugWindowLogger.h
 * @brief Dedicated logger for the Debug Window system in the Kryptos Engine.
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
     * @class DebugWindowLogger
     * @brief Provides a spdlog logger instance for Debug Window-related output.
     *
     * Configured separately from the core engine logger to enable subsystem-level logging.
     */
    class DebugWindowLogger
    {
    public:
        // -----------------------------------------------------
        // Public Static Methods
        // -----------------------------------------------------

        /**
         * @brief Initialises the Debug Window logger with custom formatting.
         */
        static void Init();

        /**
         * @brief Retrieves the Debug Window logger.
         * @return Shared pointer to the spdlog logger instance.
         */
        static std::shared_ptr<spdlog::logger>& GetLogger();

    private:
        // -----------------------------------------------------
        // Private Members
        // -----------------------------------------------------

        static std::shared_ptr<spdlog::logger> s_DebugLogger; ///< Logger for Debug Window.
    };
}
