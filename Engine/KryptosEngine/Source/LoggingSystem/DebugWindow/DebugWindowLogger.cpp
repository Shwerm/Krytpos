/*
 * DebugWindowLogger.cpp - Kryptos Debug Window Logging Implementation
 * -------------------------------------------------------------------
 * Implements the DebugWindowLogger class for managing logging specific to the Debug Window.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - DebugWindowLogger.h: Header for the DebugWindowLogger class.
 */

#include "../Include/LoggingSystem/DebugWindow/DebugWindowLogger.h"

namespace KryptosEngine {

    // Define the static logger instance
    std::shared_ptr<spdlog::logger> DebugWindowLogger::s_DebugLogger;

    /**
     * @brief Initializes the Debug Window logger.
     *
     * Sets up the logger with a custom name, output format, and debug-level logging.
     * Ensures detailed and color-coded logs for Debug Window events.
     */
    void DebugWindowLogger::Init() {
        // Create the Debug Window logger
        s_DebugLogger = spdlog::stdout_color_mt("DebugWindowLogger");
        s_DebugLogger->set_pattern("[%T] [%^%l%$] [DebugWindow] %v");
        s_DebugLogger->set_level(spdlog::level::debug); // Set logging level to debug
    }

    /**
     * @brief Retrieves the Debug Window logger instance.
     *
     * Provides access to the logger for use in Debug Window components and systems.
     * @return A shared pointer to the spdlog logger.
     */
    std::shared_ptr<spdlog::logger>& DebugWindowLogger::GetLogger() {
        return s_DebugLogger;
    }

} // namespace KryptosEngine
