/*
 * OpenGlRenderer is a type-safe OpenGL wrapper.
 */

#pragma once

#include "RendererTypes.h"

#include <glm/glm.hpp>

#include <string>

namespace Graphics
{
    struct Vertex1;

    class OpenGlRenderer
    {
    public:
        //Buffer management
        static FrameBuffer GenFrameBuffer();
        static void BindFrameBuffer(const FrameBuffer& buffer);
        static void UnbindFrameBuffer();
        static void DeleteFrameBuffer(const FrameBuffer& buffer);
        static void SetFrameBufferRenderBuffer(const RenderBuffer& buffer);
        static void SetFrameBufferTexture2d(const Texture2d& texture);
        static void AssertFrameBufferComplete();

        static RenderBuffer GenRenderBuffer();
        static void BindRenderBuffer(const RenderBuffer& buffer);
        static void UnbindRenderBuffer();
        static void DeleteRenderBuffer(const RenderBuffer& buffer);
        static void SetRenderBufferStorage(int width, int height);

        static VertexArray GenVertexArray();
        static void BindVertexArray(const VertexArray& vertexArray);
        static void UnbindVertexArray();

        static VertexBuffer GenVertexBuffer();
        static void BindVertexBuffer(const VertexBuffer& buffer);
        static void UnbindVertexBuffer();
        static void DeleteVertexBuffer(const VertexBuffer& buffer);
        static void SetVertexesForStaticDraw(size_t sizeInBytes, const std::vector<Vertex1>& vertexes);
        static void VertexBufferSubData(ptrdiff_t offset, size_t sizeInBytes, const std::vector<Vertex1>& vertexes);

        static IndexBuffer GenIndexBuffer();
        static void BindIndexBuffer(const IndexBuffer& buffer);
        static void UnbindIndexBuffer();
        static void DeleteIndexBuffer(const IndexBuffer& buffer);
        static void SetIndexesForStaticDraw(size_t sizeInBytes, const std::vector<int>& indexes);
        static void IndexBufferSubData(ptrdiff_t offset, size_t sizeInBytes, const std::vector<int>& indexes);

        static void UnbindAll();

        static void SetVertexAttrib0(int size, unsigned int type, bool isNormalized, ptrdiff_t stride, ptrdiff_t offset);
        static void SetVertexAttrib1(int size, unsigned int type, bool isNormalized, ptrdiff_t stride, ptrdiff_t offset);

        //Texture management
        static Texture2d GenTexture2d();
        static void BindTexture2d(const Texture2d& texture);
        static void UnbindTexture2d();
        static void DeleteTexture(const Texture2d& texture);
        static void TexImage2d(uint32_t width, uint32_t height);
        static void SetTexture2dParameters();

        //Shader management
        static ShaderProgram CreateShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        static void UnbindShader();
        static void UseShader(const ShaderProgram& shader);
        static void DeleteShader(const ShaderProgram& shader);

        static void SetUniform(const Uniform& uniform, float value);
        static void SetUniform(const Uniform& uniform, const glm::mat4& matrix);
        static void SetUniform(const Uniform& uniform, const glm::vec4& vec);

        static Uniform GetUniform(const ShaderProgram& shader, const std::string& uniformName);

        //Draw parameters and commands
        static void ClearColorBuffer();

        static void SetClearColor(const glm::vec4& color);
        static void SetLineWidth(float width);
        static void SetViewPort(uint32_t xPos, uint32_t yPos, uint32_t width, uint32_t height);

        static void ResetLineWidth();
        static void EnablePointSize();
        static void DisablePointSize();

        //Draw calls
        static void DrawIndexes(uint32_t mode, uint32_t indexCount);
        static void DrawTriangleIndexes(uint32_t indexCount);
        static void DrawLineIndexes(uint32_t indexCount);
        static void DrawPointIndexes(uint32_t indexCount);
    };
}
