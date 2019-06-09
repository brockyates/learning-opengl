#pragma once

#include <glad/glad.h>

namespace Graphics::Detail {

    struct ShaderProgramTag {};
    struct VertexShaderTag {};
    struct FragmentShaderTag {};
    struct FrameBufferTag {};

    template <typename Tag>
    class Uint32Id
    {
    public:
        explicit Uint32Id(const uint32_t id)
            : value_(id)
        {}

        [[nodiscard]] GLuint AsGlType() const { return static_cast<GLuint>(value_); }

    private:
        uint32_t value_;
    };

}
