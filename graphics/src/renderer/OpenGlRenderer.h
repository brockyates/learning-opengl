#pragma once

#include "RendererTypes.h"

#include <string>

namespace Graphics
{
    class OpenGlRenderer
    {
    public:
        static ShaderProgram CreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        static void LinkProgram(const ShaderProgram& program);
        static void ValidateProgram(const ShaderProgram& program);

        static void AttachVertexShader(const ShaderProgram& program, const VertexShader& shader);
        static void AttachFragmentShader(const ShaderProgram& program, const FragmentShader& shader);
        static void DeleteVertexShader(const VertexShader& shader);
        static void DeleteFragmentShader(const FragmentShader& shader);
    };
}
