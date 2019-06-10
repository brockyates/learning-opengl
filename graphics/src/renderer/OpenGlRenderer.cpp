/*
 * OpenGlRenderer is a type-safe OpenGL wrapper.
 */

#include "pch.h"
#include "OpenGlRenderer.h"

#include "detail/OpenGlRendererDetail.h"

#include "logging/Log.h"

#include "types/Vertex1.h"

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

    void OpenGlRenderer::SetVertexesForStaticDraw(const uint32_t sizeInBytes, const std::vector<Vertex1>& vertexes)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeInBytes, &vertexes[0], GL_STATIC_DRAW);
    }

    void OpenGlRenderer::VertexBufferSubData(const uint32_t offset, const uint32_t sizeInBytes,
        const std::vector<Vertex1>& vertexes)
    {
        glBufferSubData(GL_ARRAY_BUFFER, offset, sizeInBytes, &vertexes[0]);
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

    void OpenGlRenderer::SetIndexesForStaticDraw(uint32_t sizeInBytes, const std::vector<unsigned>& indexes)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInBytes, &indexes[0], GL_STATIC_DRAW);
    }

    void OpenGlRenderer::IndexBufferSubData(const uint32_t offset, const uint32_t sizeInBytes, const std::vector<unsigned int>& indexes)
    {
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, sizeInBytes, &indexes[0]);
    }

    void OpenGlRenderer::UnbindAll()
    {
        UnbindShader();
        UnbindVertexArray();
        UnbindIndexBuffer();
        UnbindFrameBuffer();
    }

    namespace
    {
        void SetVertexAttrib(const uint32_t index, const uint32_t size, const uint32_t type, const bool isNormalized, uint32_t stride,
            const size_t offset)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, size, type, isNormalized, stride, reinterpret_cast<void*>(offset));
        }
    }

    void OpenGlRenderer::SetVertexAttrib0(const uint32_t size, const uint32_t type, const bool isNormalized, uint32_t stride,
        const size_t offset)
    {
        SetVertexAttrib(0, size, type, isNormalized, stride, offset);
    }

    void OpenGlRenderer::SetVertexAttrib1(const uint32_t size, const uint32_t type, const bool isNormalized, uint32_t stride,
                                                 const size_t offset)
    {
        SetVertexAttrib(1, size, type, isNormalized, stride, offset);
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

    void OpenGlRenderer::UnbindShader()
    {
        glUseProgram(0);
    }

    void OpenGlRenderer::UseShader(const ShaderProgram& shader)
    {
        glUseProgram(shader.AsGlType());
    }

    void OpenGlRenderer::DeleteShader(const ShaderProgram& shader)
    {
        glDeleteProgram(shader.AsGlType());
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

    void OpenGlRenderer::ClearColorBuffer()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGlRenderer::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color[0], color[1], color[2], color[3]);
    }

    void OpenGlRenderer::SetLineWidth(const float width)
    {
        glLineWidth(width);
    }

    void OpenGlRenderer::SetViewPort(const uint32_t xPos, const uint32_t yPos, const uint32_t width, const uint32_t height)
    {
        glViewport(xPos, yPos, width, height);
    }

    void OpenGlRenderer::ResetLineWidth()
    {
        glLineWidth(1.0f);
    }

    void OpenGlRenderer::EnablePointSize()
    {
        glEnable(GL_PROGRAM_POINT_SIZE);
    }

    void OpenGlRenderer::DisablePointSize()
    {
        glDisable(GL_PROGRAM_POINT_SIZE);
    }

    void OpenGlRenderer::DrawTriangleIndexes(const uint32_t indexCount)
    {
        const auto mode = GL_TRIANGLES;
        const auto indexType = GL_UNSIGNED_INT;
        const auto offset = nullptr;
        glDrawElements(mode, indexCount, indexType, offset);
    }

    void OpenGlRenderer::DrawLineIndexes(const uint32_t indexCount)
    {
        const auto mode = GL_LINES;
        const auto indexType = GL_UNSIGNED_INT;
        const auto offset = nullptr;
        glDrawElements(mode, indexCount, indexType, offset);
    }
}
