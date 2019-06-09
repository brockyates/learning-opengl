/*
 * OpenGlRenderer is a type-safe OpenGL wrapper.
 */

#include "pch.h"
#include "OpenGlRenderer.h"

#include "detail/OpenGlRendererDetail.h"

#include "logging/Log.h"

#include <glad/glad.h>

namespace Graphics
{
    namespace {

        ShaderProgram CreateProgram()
        {
            return ShaderProgram{ glCreateProgram() };
        }

        void LinkProgram(const ShaderProgram& program)
        {
            glLinkProgram(program.AsGlType());
        }

        void ValidateProgram(const ShaderProgram& program)
        {
            glValidateProgram(program.AsGlType());
        }

        void AttachVertexShader(const ShaderProgram& program, const VertexShader& shader)
        {
            glAttachShader(program.AsGlType(), shader.AsGlType());
        }

        void AttachFragmentShader(const ShaderProgram& program, const FragmentShader& shader)
        {
            glAttachShader(program.AsGlType(), shader.AsGlType());
        }

        void DeleteVertexShader(const VertexShader& shader)
        {
            glDeleteShader(shader.AsGlType());
        }

        void DeleteFragmentShader(const FragmentShader& shader)
        {
            glDeleteShader(shader.AsGlType());
        }

    }

    void OpenGlRenderer::BindFrameBuffer(const FrameBuffer& buffer)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, buffer.AsGlType());
    }

    void OpenGlRenderer::UnbindFrameBuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    ShaderProgram OpenGlRenderer::CreateShaderProgram(const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath)
    {
        LogGlTrace([&]()
        {
            std::stringstream ss;
            ss << "Creating shader: {VertexShader:\"" << vertexShaderPath << R"(", FragmentShader:")" << fragmentShaderPath << "\"}";
            return ss.str();
        }());

        const auto program = CreateProgram();
        const auto vertexShader = Detail::Compile<VertexShader>(vertexShaderPath);
        const auto fragmentShader = Detail::Compile<FragmentShader>(fragmentShaderPath);

        AttachVertexShader(program, vertexShader);
        AttachFragmentShader(program, fragmentShader);
        LinkProgram(program);
        ValidateProgram(program);

        DeleteVertexShader(vertexShader);
        DeleteFragmentShader(fragmentShader);

        return program;
    }
}
