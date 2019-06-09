#pragma once

#include <glad/glad.h>

namespace Graphics::Detail {

    struct ProgramIdTag {};

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

namespace Graphics {

#ifdef OPENGL_RENDERER
    class OpenGlRenderer;
    using Renderer = OpenGlRenderer;
#else
    class TestRenderer;
    using Renderer = TestRenderer;
#endif //OPENGL_RENDERER

    using ProgramId = Detail::Uint32Id<Detail::ProgramIdTag>;

}
