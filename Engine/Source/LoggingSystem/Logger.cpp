/**
 * @file Logger.cpp
 * @brief Implements the core logging system using spdlog for the Kryptos Engine.
 *
 * @ingroup LoggingSystem
 *
 * Provides coloured console output and persistent file logging to support debugging,
 * profiling, and engine diagnostics. Accessible globally via static interface.
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../Include/LoggingSystem/Logger.h"

namespace KryptosEngine
{
    // -----------------------------------------------------
    // Static Members
    // -----------------------------------------------------

    std::shared_ptr<spdlog::logger> Logger::s_Logger;

    // -----------------------------------------------------
    // Public Static Methods
    // -----------------------------------------------------

    /**
     * @brief Initialises the main logging system for the engine.
     *
     * Creates both a console sink and a file sink, sets formatting,
     * and registers the logger globally with spdlog.
     */
    void Logger::Init()
    {
        // Setup sinks
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/engine.log", true);

        // Set message format for each sink
        console_sink->set_pattern("[%T] [%^%l%$] %v"); // coloured level for console
        file_sink->set_pattern("[%T] [%l] %v");        // plain level for log file

        // Combine sinks into one logger
        s_Logger = std::make_shared<spdlog::logger>("EngineLogger", spdlog::sinks_init_list{ console_sink, file_sink });
        spdlog::register_logger(s_Logger);
        spdlog::set_default_logger(s_Logger);

        // Set log level and flush policy
        s_Logger->set_level(spdlog::level::info);   // Default verbosity
        s_Logger->flush_on(spdlog::level::warn);    // Flush if warning or above
    }

    /**
     * @brief Returns the shared pointer to the engine logger instance.
     *
     * Useful for modules that need scoped or contextual logging.
     * @return Shared pointer to the spdlog logger.
     */
    std::shared_ptr<spdlog::logger>& Logger::GetLogger()
    {
        return s_Logger;
    }

} // namespace KryptosEngine
