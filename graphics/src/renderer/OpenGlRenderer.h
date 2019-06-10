/*
 * OpenGlRenderer is a type-safe OpenGL wrapper.
 */

#pragma once

#include "RendererTypes.h"

#include <glm/glm.hpp>

#include <string>

namespace Graphics
{
    class OpenGlRenderer
    {
    public:
        static void BindFrameBuffer(const FrameBuffer& buffer);
        static void UnbindFrameBuffer();

        static VertexArray GenVertexArray();
        static void BindVertexArray(const VertexArray& vertexArray);
        static void UnbindVertexArray();

        static VertexBuffer GenVertexBuffer();
        static void BindVertexBuffer(const VertexBuffer& buffer);
        static void UnbindVertexBuffer();
        static void DeleteVertexBuffer(const VertexBuffer& buffer);

        static IndexBuffer GenIndexBuffer();
        static void BindIndexBuffer(const IndexBuffer& buffer);
        static void UnbindIndexBuffer();
        static void DeleteIndexBuffer(const IndexBuffer& buffer);

        static ShaderProgram CreateShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        static void UnbindProgram();

        static void SetUniform(const Uniform& uniform, const glm::mat4& matrix);
        static void SetUniform(const Uniform& uniform, const glm::vec4& vec);
        static Uniform GetUniform(const ShaderProgram& shader, const std::string& uniformName);
    };
}
