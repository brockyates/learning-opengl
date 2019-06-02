#include "pch.h"
#include "Log.h"

#include <spdlog/sinks/ostream_sink.h>

namespace Graphics::Utils
{

    std::shared_ptr<spdlog::logger> Log::logger_;
    std::shared_ptr<spdlog::logger> Log::openGlLogger_;
    std::ostringstream Log::logStream_;

    void Log::Init()
    {
        auto sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(logStream_);
        const auto pattern = "%^[%T] [%l] [%n] %v%$";

        logger_ = std::make_shared<spdlog::logger>("Graphics", sink);
        logger_->set_level(spdlog::level::trace);
        logger_->set_pattern(pattern);

        openGlLogger_ = std::make_shared<spdlog::logger>("OpenGL", sink);
        openGlLogger_->set_level(spdlog::level::trace);
        openGlLogger_->set_pattern(pattern);

        LOG_INFO("spdlog initialized");
    }
}
