#pragma once

#ifdef APP_DEBUG
    #define APP_ENABLE_ASSERTS
#endif // APP_DEBUG

#ifdef APP_ENABLE_ASSERTS
    #define APP_ASSERT(x, ...) { if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define APP_ASSERT(x, ...)
#endif // APP_ENABLE_ASSERTS

#define BIT(x) (1 << x)
