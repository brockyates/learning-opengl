#pragma once

#include "RendererTypes.h"

#include <string>

namespace Graphics
{
    class OpenGlRenderer
    {
    public:
        static ShaderProgram CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    };
}
