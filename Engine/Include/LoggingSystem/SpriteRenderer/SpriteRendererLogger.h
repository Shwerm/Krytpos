#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>

namespace KryptosEngine {

    class SpriteRendererLogger {
    public:
        // Initializes the Sprite Renderer Logger
        static void Init();

        // Retrieves the Sprite Renderer Logger
        static std::shared_ptr<spdlog::logger>& GetLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_SpriteLogger; // Logger instance for Sprite Rendering
    };

} // namespace KryptosEngine
