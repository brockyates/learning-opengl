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

#define GLCall(x) GLClearError(); x; APP_ASSERT(GLLogCallError(#x, __FILE__, __LINE__), "OpenGL error");
#define GLLoggedCall(x) GLClearError(); x; APP_ASSERT(GLLogCallError(#x, __FILE__, __LINE__), "OpenGL error"); GLLogCall(#x, __FILE__, __LINE__);

namespace Graphics {

    void GLClearError();
    void GLLogCall(const char* function, const char* file, int line);
    bool GLLogCallError(const char* function, const char* file, int line);

}
