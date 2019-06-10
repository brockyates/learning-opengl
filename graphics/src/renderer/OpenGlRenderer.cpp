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

    VertexArray OpenGlRenderer::GenVertexArray()
    {
        uint32_t id;
        glGenVertexArrays(1, &id);

        return VertexArray{ id };
    }

    void OpenGlRenderer::BindVertexArray(const VertexArray& vertexArray)
    {
        glBindVertexArray(vertexArray.AsGlType());
    }

    void OpenGlRenderer::UnbindVertexArray()
    {
        glBindVertexArray(0);
    }

    VertexBuffer OpenGlRenderer::GenVertexBuffer()
    {
        uint32_t id;
        glGenBuffers(1, &id);

        return VertexBuffer{ id };
    }

    void OpenGlRenderer::BindVertexBuffer(const VertexBuffer& buffer)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffer.AsGlType());
    }

    void OpenGlRenderer::UnbindVertexBuffer()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void OpenGlRenderer::DeleteVertexBuffer(const VertexBuffer& buffer)
    {
        const auto id = buffer.AsGlType();
        glDeleteBuffers(1, &id);
    }

    IndexBuffer OpenGlRenderer::GenIndexBuffer()
    {
        uint32_t id;
        glGenBuffers(1, &id);

        return IndexBuffer{ id };
    }

    void OpenGlRenderer::BindIndexBuffer(const IndexBuffer& buffer)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.AsGlType());
    }

    void OpenGlRenderer::UnbindIndexBuffer()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void OpenGlRenderer::DeleteIndexBuffer(const IndexBuffer& buffer)
    {
        const auto id = buffer.AsGlType();
        glDeleteBuffers(1, &id);
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

    void OpenGlRenderer::UnbindProgram()
    {
        glUseProgram(0);
    }

    void OpenGlRenderer::SetUniform(const Uniform& uniform, const glm::mat4& matrix)
    {
        const auto count = 1;
        const auto transpose = GL_FALSE;
        glUniformMatrix4fv(uniform.AsGlType(), count, transpose, &matrix[0][0]);
    }

    void OpenGlRenderer::SetUniform(const Uniform& uniform, const glm::vec4& vec)
    {
        const auto count = 1;
        glUniform4fv(uniform.AsGlType(), count, &vec[0]);
    }

    Uniform OpenGlRenderer::GetUniform(const ShaderProgram& shader, const std::string& uniformName)
    {
        return Uniform{ glGetUniformLocation(shader.AsGlType(), uniformName.c_str()) };
    }
}
