#pragma once

#include <glad/glad.h>

namespace Graphics::Detail
{
    struct FragmentShaderTag {};
    struct FrameBufferTag {};
    struct IndexBufferTag {};
    struct RenderBufferTag {};
    struct ShaderProgramTag {};
    struct Texture2dTag {};
    struct VertexArrayTag {};
    struct VertexBufferTag {};
    struct VertexShaderTag {};

    template <typename Tag>
    class UintId
    {
    public:
        UintId()
            : value_(0)
        {}

        explicit UintId(const unsigned int id)
            : value_(id)
        {}

        [[nodiscard]] GLuint AsGlType() const { return static_cast<GLuint>(value_); }

    private:
        unsigned int value_;
    };
}
