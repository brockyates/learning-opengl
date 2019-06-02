#pragma once

#include <glad/glad.h>

namespace Graphics {

    void GLAPIENTRY GL_DEBUG_MESSAGE_CALLBACK(GLenum source,
                                           GLenum type,
                                           GLuint id,
                                           GLenum severity,
                                           GLsizei length,
                                           const GLchar* message,
                                           const void* userParam);

}
