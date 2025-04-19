/**
 * @file DebugWindowLogger.cpp
 * @brief Implements a dedicated logger for the Debug Window subsystem.
 *
 * @ingroup LoggingSystem
 *
 * This logger is used to output messages specific to the Debug Window interface,
 * including initialization messages, toggle actions, and error states.
 * Logs to the console with its own format and tag.
 *
 * Author:
 * Sam Camilleri, Mural Studios
 * @version 1.0
 * @date 2025
 */

#include "../../../Include/LoggingSystem/DebugWindow/DebugWindowLogger.h"

namespace KryptosEngine
{
    // -----------------------------------------------------
    // Static Members
    // -----------------------------------------------------

    std::shared_ptr<spdlog::logger> DebugWindowLogger::s_DebugLogger;

    // -----------------------------------------------------
    // Public Static Methods
    // -----------------------------------------------------

    /**
     * @brief Initialises the Debug Window logger instance.
     *
     * Configures the output format, name, and log level specifically for debug UI.
     */
    void DebugWindowLogger::Init()
    {
        s_DebugLogger = spdlog::stdout_color_mt("DebugWindowLogger");
        s_DebugLogger->set_pattern("[%T] [%^%l%$] [DebugWindow] %v");
        s_DebugLogger->set_level(spdlog::level::debug);
    }

    /**
     * @brief Retrieves the Debug Window logger.
     * @return Shared pointer to the debug logger instance.
     */
    std::shared_ptr<spdlog::logger>& DebugWindowLogger::GetLogger()
    {
        return s_DebugLogger;
    }

} // namespace KryptosEngine
