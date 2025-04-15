#include "../../../Include/LoggingSystem/SpriteRenderer/SpriteRendererLogger.h"

namespace KryptosEngine {
    // Define the static logger instance
    std::shared_ptr<spdlog::logger> SpriteRendererLogger::s_SpriteLogger;

    void SpriteRendererLogger::Init() {
        // Create the Sprite Renderer logger
        s_SpriteLogger = spdlog::stdout_color_mt("SpriteRendererLogger");
        s_SpriteLogger->set_pattern("[%T] [%^%l%$] [SpriteRenderer] %v");
        s_SpriteLogger->set_level(spdlog::level::debug);
    }

    std::shared_ptr<spdlog::logger>& SpriteRendererLogger::GetLogger() {
        return s_SpriteLogger;
    }
}
