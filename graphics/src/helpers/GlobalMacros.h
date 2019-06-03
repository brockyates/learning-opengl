#pragma once

#include "logging/Log.h"

#ifdef APP_DEBUG
    #define APP_ENABLE_ASSERTS
#endif // APP_DEBUG

#ifdef APP_ENABLE_ASSERTS
    
    template <typename T, typename... Ts>
    constexpr void AppAssert(T x, Ts... args)
    {
        if (!(x))
        {
            LogError("Assertion Failed: {0}", args...);
            __debugbreak();
        }
    }

#else
    #define AppAssert(x, ...)
#endif // APP_ENABLE_ASSERTS
