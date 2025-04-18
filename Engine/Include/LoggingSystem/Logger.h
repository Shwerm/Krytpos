/**
 * @file Logger.h
 * @brief Centralised logging interface for the Kryptos Engine using spdlog.
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
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>

namespace KryptosEngine
{
    /**
     * @class Logger
     * @brief Provides a default logger instance for global logging across the engine.
     *
     * Supports both console and file-based logging, configured at engine startup.
     */
    class Logger
    {
    public:
        // -----------------------------------------------------
        // Public Static Methods
        // -----------------------------------------------------

        /**
         * @brief Initialises the general logging system.
         *
         * Configures logging sinks and formatting rules.
         */
        static void Init();

        /**
         * @brief Retrieves the global engine logger.
         * @return Shared pointer to the spdlog logger.
         */
        static std::shared_ptr<spdlog::logger>& GetLogger();

    private:
        // -----------------------------------------------------
        // Private Members
        // -----------------------------------------------------

        static std::shared_ptr<spdlog::logger> s_Logger; ///< Global logger instance.
    };
}
