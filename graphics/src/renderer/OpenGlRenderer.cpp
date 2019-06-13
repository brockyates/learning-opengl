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
    namespace
    {
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

    FrameBuffer OpenGlRenderer::GenFrameBuffer()
    {
        uint32_t id;
        glGenFramebuffers(1, &id);
        return FrameBuffer{ id };
    }

    void OpenGlRenderer::BindFrameBuffer(const FrameBuffer& buffer)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, buffer.AsGlType());
    }

    void OpenGlRenderer::UnbindFrameBuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGlRenderer::DeleteFrameBuffer(const FrameBuffer& buffer)
    {
        const auto id = buffer.AsGlType();
        glDeleteFramebuffers(1, &id);
    }

    void OpenGlRenderer::SetFrameBufferRenderBuffer(const RenderBuffer& buffer)
    {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, buffer.AsGlType());
    }

    void OpenGlRenderer::SetFrameBufferTexture2d(const Texture2d& texture)
    {
        const auto level = 0;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.AsGlType(), level);
    }

    void OpenGlRenderer::AssertFrameBufferComplete()
    {
        const auto frameBufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (!(frameBufferStatus == GL_FRAMEBUFFER_COMPLETE))
        {
            LogGlError([frameBufferStatus]() {
                std::stringstream ss;
                ss << "Frame buffer status error. Status: " << std::hex << frameBufferStatus;
                return ss.str();
            }());

            AppAssert(false, "Frame buffer is not complete. Exiting.");
        }
        else
        {
            LogGlTrace("Frame buffer complete");
        }
    }

    RenderBuffer OpenGlRenderer::GenRenderBuffer()
    {
        uint32_t id;
        glGenRenderbuffers(1, &id);
        return RenderBuffer{ id };
    }

    void OpenGlRenderer::BindRenderBuffer(const RenderBuffer& buffer)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, buffer.AsGlType());
    }

    void OpenGlRenderer::UnbindRenderBuffer()
    {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    void OpenGlRenderer::DeleteRenderBuffer(const RenderBuffer& buffer)
    {
        const auto id = buffer.AsGlType();
        glDeleteBuffers(1, &id);
    }

    void OpenGlRenderer::SetRenderBufferStorage(int width, int height)
    {
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
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

    void OpenGlRenderer::SetVertexesForStaticDraw(size_t sizeInBytes, const std::vector<Vertex1>& vertexes)
    {
        glBufferData(GL_ARRAY_BUFFER, sizeInBytes, &vertexes[0], GL_STATIC_DRAW);
    }

    void OpenGlRenderer::VertexBufferSubData(ptrdiff_t offset, size_t sizeInBytes,
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

    void OpenGlRenderer::SetIndexesForStaticDraw(size_t sizeInBytes, const std::vector<int>& indexes)
    {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInBytes, &indexes[0], GL_STATIC_DRAW);
    }

    void OpenGlRenderer::IndexBufferSubData(ptrdiff_t offset, size_t sizeInBytes, const std::vector<int>& indexes)
    {
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, sizeInBytes, &indexes[0]);
    }

    void OpenGlRenderer::UnbindAll()
    {
        UnbindTexture2d();
        UnbindShader();
        UnbindVertexArray();
        UnbindIndexBuffer();
        UnbindFrameBuffer();
        UnbindRenderBuffer();
    }

    namespace
    {
        void SetVertexAttrib(const int index, const int size, const unsigned int type, const bool isNormalized, const ptrdiff_t stride,
            const ptrdiff_t offset)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, size, type, isNormalized, static_cast<int>(stride), reinterpret_cast<void*>(offset));
        }
    }

    void OpenGlRenderer::SetVertexAttrib0(const int size, const unsigned int type, const bool isNormalized, const ptrdiff_t stride,
        const ptrdiff_t offset)
    {
        SetVertexAttrib(0, size, type, isNormalized, stride, offset);
    }

    void OpenGlRenderer::SetVertexAttrib1(const int size, const unsigned int type, const bool isNormalized, const ptrdiff_t stride,
        const ptrdiff_t offset)
    {
        SetVertexAttrib(1, size, type, isNormalized, stride, offset);
    }

    Texture2d OpenGlRenderer::GenTexture2d()
    {
        uint32_t id;
        glGenTextures(1, &id);
        return Texture2d{ id };
    }

    void OpenGlRenderer::BindTexture2d(const Texture2d& texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture.AsGlType());
    }

    void OpenGlRenderer::UnbindTexture2d()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGlRenderer::DeleteTexture(const Texture2d& texture)
    {
        const auto id = texture.AsGlType();
        glDeleteTextures(1, &id);
    }

    void OpenGlRenderer::TexImage2d(int width, int height)
    {
        const auto level = 0;
        const auto border = 0;
        const auto pixels = nullptr;
        glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, width, height, border, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    }

    void OpenGlRenderer::SetTexture2dParameters()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    ShaderProgram OpenGlRenderer::CreateShaderProgram(const std::string& vertexShaderPath,
        const std::string& fragmentShaderPath)
    {
        LogGlTrace([vertexShaderPath, fragmentShaderPath]()
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

    void OpenGlRenderer::SetUniform(const Uniform& uniform, const float value)
    {
        glUniform1f(uniform.AsGlType(), value);
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

    void OpenGlRenderer::SetViewPort(int xPos, int yPos, int width, int height)
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

    void OpenGlRenderer::DrawIndexes(unsigned mode, int indexCount)
    {
        const auto indexType = GL_UNSIGNED_INT;
        const auto offset = nullptr;
        glDrawElements(mode, indexCount, indexType, offset);
    }

    void OpenGlRenderer::DrawTriangleIndexes(int indexCount)
    {
        DrawIndexes(GL_TRIANGLES, indexCount);
    }

    void OpenGlRenderer::DrawLineIndexes(int indexCount)
    {
        DrawIndexes(GL_LINES, indexCount);
    }

    void OpenGlRenderer::DrawPointIndexes(int indexCount)
    {
        DrawIndexes(GL_POINTS, indexCount);
    }
}
