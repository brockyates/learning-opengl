#pragma once

#include <glad/glad.h>

namespace Graphics {

    void GLAPIENTRY GLDebugMessageCallback(GLenum source,
                                           GLenum type,
                                           GLuint id,
                                           GLenum severity,
                                           GLsizei length,
                                           const GLchar* message,
                                           const void* userParam);

}
