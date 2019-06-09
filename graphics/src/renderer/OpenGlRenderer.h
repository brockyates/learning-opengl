/*
 * OpenGlRenderer is a type-safe OpenGL wrapper.
 */

#pragma once

#include "RendererTypes.h"

#include <string>

namespace Graphics
{
    class OpenGlRenderer
    {
    public:
        static ShaderProgram CreateShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    };
}
