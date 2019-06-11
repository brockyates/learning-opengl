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
    class Uint32Id
    {
    public:
        Uint32Id()
            : value_(0)
        {}

        explicit Uint32Id(const uint32_t id)
            : value_(id)
        {}

        [[nodiscard]] GLuint AsGlType() const { return static_cast<GLuint>(value_); }

    private:
        uint32_t value_;
    };
}
