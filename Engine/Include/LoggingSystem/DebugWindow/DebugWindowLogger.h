/*
 * DebugWindowLogger.h - Kryptos Debug Window Logging System
 * ---------------------------------------------------------
 * Provides a dedicated logging system for the Debug Window in the Kryptos engine.
 * Utilizes spdlog for efficient console-based logging.
 *
 * Author: Sam Camilleri, Mural Studios
 * All Rights Reserved, 2025.
 *
 * Dependencies:
 *   - spdlog/spdlog.h: Core logging functionalities.
 *   - spdlog/sinks/stdout_color_sinks.h: For colored console output.
 *   - memory: For managing shared pointers.
 */

#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace KryptosEngine {

    /**
     * @class DebugWindowLogger
     * @brief Provides logging functionality specific to the Debug Window.
     *
     * The DebugWindowLogger class initializes and manages a dedicated logger
     * for use with the Debug Window, enabling detailed debugging information.
     */
    class DebugWindowLogger {
    public:
        /**
         * @brief Initializes the Debug Window logger.
         *
         * Configures the logger with a specific format and debug-level logging.
         */
        static void Init();

        /**
         * @brief Retrieves the Debug Window logger instance.
         *
         * Provides access to the initialized logger for use in Debug Window components.
         * @return A shared pointer to the spdlog logger.
         */
        static std::shared_ptr<spdlog::logger>& GetLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_DebugLogger; ///< Logger instance for the Debug Window.
    };

} // namespace KryptosEngine
