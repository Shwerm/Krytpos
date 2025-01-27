#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <memory>

namespace KryptosEngine {

    class Logger {
    public:
        // Initializes the general logging system
        static void Init();

        // Retrieves the default logger
        static std::shared_ptr<spdlog::logger>& GetLogger();

    private:
        static std::shared_ptr<spdlog::logger> s_Logger; // Default engine logger
    };

} // namespace KryptosEngine
