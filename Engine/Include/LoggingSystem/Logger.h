/*
 * Logger.h - Kryptos Engine Logging System
 * ----------------------------------------
 * Provides a centralized logging system for the Kryptos engine, utilizing spdlog.
 * Supports console and file-based logging with customizable log levels.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - spdlog/spdlog.h: Core logging functionalities.
 *   - spdlog/sinks/stdout_color_sinks.h: For colored console output.
 *   - spdlog/sinks/basic_file_sink.h: For file-based logging.
 *   - memory: For managing shared pointers.
 */

#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>

namespace KryptosEngine {

    /**
     * @class Logger
     * @brief Provides a centralized logging system for the Kryptos engine.
     *
     * The Logger class initializes a default logger and provides access to it
     * for consistent logging throughout the engine. Supports both console and
     * file-based logging.
     */
    class Logger {
    public:
        /**
         * @brief Initializes the general logging system.
         *
         * Sets up the logging sinks, formats, and default logger.
         * Ensures logging is ready to use at engine startup.
         */
        static void Init();

        /**
         * @brief Retrieves the default logger instance.
         *
         * Provides access to the initialized logger for use in other components.
         * @return A shared pointer to the spdlog logger.
         */
        static std::shared_ptr<spdlog::logger>& GetLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_Logger; ///< Default engine logger.
    };

} // namespace KryptosEngine
