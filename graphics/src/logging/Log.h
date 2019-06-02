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
    constexpr void LOG_TRACE(Ts... args)
    {
        ::Graphics::Utils::Log::GetLogger()->trace(args...);
    }

    template <typename... Ts>
    constexpr void LOG_INFO(Ts... args)
    {
        ::Graphics::Utils::Log::GetLogger()->info(args...);
    }

    template <typename... Ts>
    constexpr void LOG_WARN(Ts... args)
    {
        ::Graphics::Utils::Log::GetLogger()->warn(args...);
    }

    template <typename... Ts>
    constexpr void LOG_ERROR(Ts... args)
    {
        ::Graphics::Utils::Log::GetLogger()->error(args...);
    }

    template <typename... Ts>
    constexpr void LOG_DEBUG(Ts... args)
    {
        ::Graphics::Utils::Log::GetLogger()->debug(args...);
    }

    template <typename... Ts>
    constexpr void LOG_CRITICAL(Ts... args)
    {
        ::Graphics::Utils::Log::GetLogger()->critical(args...);
    }

    // OpenGL Log macros
    template <typename... Ts>
    constexpr void LOG_GL_TRACE(Ts... args)
    {
        ::Graphics::Utils::Log::GetOpenGlLogger()->trace(args...);
    }

    template <typename... Ts>
    constexpr void LOG_GL_INFO(Ts... args)
    {
        ::Graphics::Utils::Log::GetOpenGlLogger()->info(args...);
    }

    template <typename... Ts>
    constexpr void LOG_GL_WARN(Ts... args)
    {
        ::Graphics::Utils::Log::GetOpenGlLogger()->warn(args...);
    }

    template <typename... Ts>
    constexpr void LOG_GL_ERROR(Ts... args)
    {
        ::Graphics::Utils::Log::GetOpenGlLogger()->error(args...);
    }

    template <typename... Ts>
    constexpr void LOG_GL_DEBUG(Ts... args)
    {
        ::Graphics::Utils::Log::GetOpenGlLogger()->debug(args...);
    }

    template <typename... Ts>
    constexpr void LOG_GL_CRITICAL(Ts... args)
    {
        ::Graphics::Utils::Log::GetOpenGlLogger()->critical(args...);
    }

#else
    // Application Log macros
    #define LOG_TRACE(...)
    #define LOG_INFO(...)
    #define LOG_WARN(...)
    #define LOG_ERROR(...)
    #define LOG_DEBUG(...)
    #define LOG_CRITICAL(...)

    // OpenGL Log macros
    #define LOG_GL_TRACE(...)
    #define LOG_GL_INFO(...)
    #define LOG_GL_WARN(...)
    #define LOG_GL_ERROR(...)
    #define LOG_GL_DEBUG(...)
    #define LOG_GL_CRITICAL(...)
#endif // APP_ENABLE_LOGGING
