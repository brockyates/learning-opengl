#pragma once
#include "spdlog/spdlog.h"

#include <memory>
#include <sstream>

namespace Graphics { namespace Utils {

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

}}

#ifdef APP_DEBUG
    #define APP_ENABLE_LOGGING
#endif // APP_DEBUG

#ifdef APP_ENABLE_LOGGING
    // Application Log macros
    template <typename... Ts>
    constexpr void LogTrace(Ts... args)
    {
        Graphics::Utils::Log::GetLogger()->trace(args...);
    }

    template <typename... Ts>
    constexpr void LogInfo(Ts... args)
    {
        Graphics::Utils::Log::GetLogger()->info(args...);
    }

    template <typename... Ts>
    constexpr void LogWarn(Ts... args)
    {
        Graphics::Utils::Log::GetLogger()->warn(args...);
    }

    template <typename... Ts>
    constexpr void LogError(Ts... args)
    {
        Graphics::Utils::Log::GetLogger()->error(args...);
    }

    template <typename... Ts>
    constexpr void LogDebug(Ts... args)
    {
        Graphics::Utils::Log::GetLogger()->debug(args...);
    }

    template <typename... Ts>
    constexpr void LogCritical(Ts... args)
    {
        Graphics::Utils::Log::GetLogger()->critical(args...);
    }

    // OpenGL Log macros
    template <typename... Ts>
    constexpr void LogGlTrace(Ts... args)
    {
        Graphics::Utils::Log::GetOpenGlLogger()->trace(args...);
    }

    template <typename... Ts>
    constexpr void LogGlInfo(Ts... args)
    {
        Graphics::Utils::Log::GetOpenGlLogger()->info(args...);
    }

    template <typename... Ts>
    constexpr void LogGlWarn(Ts... args)
    {
        Graphics::Utils::Log::GetOpenGlLogger()->warn(args...);
    }

    template <typename... Ts>
    constexpr void LogGlError(Ts... args)
    {
        Graphics::Utils::Log::GetOpenGlLogger()->error(args...);
    }

    template <typename... Ts>
    constexpr void LogGlDebug(Ts... args)
    {
        Graphics::Utils::Log::GetOpenGlLogger()->debug(args...);
    }

    template <typename... Ts>
    constexpr void LogGlCritical(Ts... args)
    {
        Graphics::Utils::Log::GetOpenGlLogger()->critical(args...);
    }

#else
    // Application Log macros
    #define LogTrace(...)
    #define LogInfo(...)
    #define LogWarn(...)
    #define LogError(...)
    #define LogDebug(...)
    #define LogCritical(...)

    // OpenGL Log macros
    #define LogGlTrace(...)
    #define LogGlInfo(...)
    #define LogGlWarn(...)
    #define LogGlError(...)
    #define LogGlDebug(...)
    #define LogGlCritical(...)
#endif // APP_ENABLE_LOGGING
