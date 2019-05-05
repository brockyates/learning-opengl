#pragma once
#include "GlobalMacros.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Graphics {

    #define GLCall(x) GLClearError(); x; APP_ASSERT(GLLogCallError(#x, __FILE__, __LINE__), "OpenGL error");
    #define GLLoggedCall(x) GLClearError(); x; APP_ASSERT(GLLogCallError(#x, __FILE__, __LINE__), "OpenGL error"); GLLogCall(#x, __FILE__, __LINE__);

    void GLClearError();
    void GLLogCall(const char* function, const char* file, int line);
    bool GLLogCallError(const char* function, const char* file, int line);

    class Renderer {
    public:
        Renderer();
        ~Renderer();
    };

}
