/*
 * Logger.cpp - Kryptos Engine Logging System Implementation
 * ---------------------------------------------------------
 * Implements the Logger class for initializing and accessing the Kryptos engine's logging system.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - Logger.h: Header for the Logger class.
 */

#include "../Include/LoggingSystem/Logger.h"

namespace KryptosEngine {

    // Define the static logger instance
    std::shared_ptr<spdlog::logger> Logger::s_Logger;

    /**
     * @brief Initializes the general logging system.
     *
     * Configures logging sinks for console and file output, sets default patterns,
     * and initializes the default logger for the engine.
     */
    void Logger::Init() {
        // Create sinks for both console and file output
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/engine.log", true);

        // Configure output format for sinks
        console_sink->set_pattern("[%T] [%^%l%$] %v");
        file_sink->set_pattern("[%T] [%l] %v");

        // Create the default logger with multiple sinks
        s_Logger = std::make_shared<spdlog::logger>("EngineLogger", spdlog::sinks_init_list{ console_sink, file_sink });
        spdlog::register_logger(s_Logger);

        // Set the logger as the default
        spdlog::set_default_logger(s_Logger);

        // Set log level and flush level
        s_Logger->set_level(spdlog::level::info); // Default log level
        s_Logger->flush_on(spdlog::level::warn);  // Flush warnings or higher
    }

    /**
     * @brief Retrieves the default logger instance.
     *
     * Provides access to the logger initialized during engine startup.
     * @return A shared pointer to the spdlog logger.
     */
    std::shared_ptr<spdlog::logger>& Logger::GetLogger() {
        return s_Logger;
    }

} // namespace KryptosEngine
