#pragma once
#include "spdlog/spdlog.h"

#include <memory>
#include <sstream>

namespace Graphics::Utils
{
    class Log
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetLogger() { return logger_; }
        static std::shared_ptr<spdlog::logger>& GetOpenGlLogger() { return openGlLogger_; }

        static const std::ostringstream& GetLogStream() { return logStream_; }

    private:
        static std::shared_ptr<spdlog::logger> logger_;
        static std::shared_ptr<spdlog::logger> openGlLogger_;
        static std::ostringstream logStream_;
    };
}

template <typename... Ts>
constexpr void LogInfo(Ts... args)
{
    Graphics::Utils::Log::GetLogger()->info(args...);
}

template <typename... Ts>
constexpr void LogError(Ts... args)
{
    Graphics::Utils::Log::GetLogger()->error(args...);
}

template <typename... Ts>
constexpr void LogCritical(Ts... args)
{
    Graphics::Utils::Log::GetLogger()->critical(args...);
}

template <typename... Ts>
constexpr void LogGlInfo(Ts... args)
{
    Graphics::Utils::Log::GetOpenGlLogger()->info(args...);
}

template <typename... Ts>
constexpr void LogGlError(Ts... args)
{
    Graphics::Utils::Log::GetOpenGlLogger()->error(args...);
}

template <typename... Ts>
constexpr void LogGlCritical(Ts... args)
{
    Graphics::Utils::Log::GetOpenGlLogger()->critical(args...);
}

#ifdef APP_DEBUG
    #define APP_ENABLE_DEBUG_LOGGING
#endif // APP_DEBUG

#ifdef APP_ENABLE_DEBUG_LOGGING
    // Application Log macros
    template <typename... Ts>
    constexpr void LogTrace(Ts... args)
    {
        Graphics::Utils::Log::GetLogger()->trace(args...);
    }

    template <typename... Ts>
    constexpr void LogWarn(Ts... args)
    {
        Graphics::Utils::Log::GetLogger()->warn(args...);
    }

    template <typename... Ts>
    constexpr void LogDebug(Ts... args)
    {
        Graphics::Utils::Log::GetLogger()->debug(args...);
    }

    // OpenGL Log macros
    template <typename... Ts>
    constexpr void LogGlTrace(Ts... args)
    {
        Graphics::Utils::Log::GetOpenGlLogger()->trace(args...);
    }

    template <typename... Ts>
    constexpr void LogGlWarn(Ts... args)
    {
        Graphics::Utils::Log::GetOpenGlLogger()->warn(args...);
    }

    template <typename... Ts>
    constexpr void LogGlDebug(Ts... args)
    {
        Graphics::Utils::Log::GetOpenGlLogger()->debug(args...);
    }

#else
    // Application Log macros
    #define LogTrace(...)
    #define LogWarn(...)
    #define LogDebug(...)

    // OpenGL Log macros
    #define LogGlTrace(...)
    #define LogGlWarn(...)
    #define LogGlDebug(...)
#endif // APP_ENABLE_DEBUG_LOGGING
