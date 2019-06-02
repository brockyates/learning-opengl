#pragma once

#include "logging/Log.h"

#ifdef APP_DEBUG
    #define APP_ENABLE_ASSERTS
#endif // APP_DEBUG

#ifdef APP_ENABLE_ASSERTS
    
    template <typename T, typename... Ts>
    void APP_ASSERT(T x, Ts... args)
    {
        if (!(x))
        {
            LOG_ERROR("Assertion Failed: {0}", args...);
            __debugbreak();
        }
    }

#else
    #define APP_ASSERT(x, ...)
#endif // APP_ENABLE_ASSERTS
