#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace KryptosEngine {

    class DebugWindowLogger {
    public:
        // Initializes the Debug Window logger
        static void Init();

        // Retrieves the Debug Window logger
        static std::shared_ptr<spdlog::logger>& GetLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_DebugLogger; // Logger instance for Debug Window
    };

} // namespace KryptosEngine
