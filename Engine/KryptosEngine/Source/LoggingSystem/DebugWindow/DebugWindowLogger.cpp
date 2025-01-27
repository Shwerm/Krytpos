#include "../Include/LoggingSystem/DebugWindow/DebugWindowLogger.h"

namespace KryptosEngine {
    // Define the static logger instance
    std::shared_ptr<spdlog::logger> DebugWindowLogger::s_DebugLogger;

    void DebugWindowLogger::Init() {
        // Create the Debug Window logger
        s_DebugLogger = spdlog::stdout_color_mt("DebugWindowLogger");
        s_DebugLogger->set_pattern("[%T] [%^%l%$] [DebugWindow] %v");
        s_DebugLogger->set_level(spdlog::level::debug);
    }

    std::shared_ptr<spdlog::logger>& DebugWindowLogger::GetLogger() {
        return s_DebugLogger;
    }
}
