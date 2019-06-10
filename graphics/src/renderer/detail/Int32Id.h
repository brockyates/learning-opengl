#pragma once

#include <glad/glad.h>

namespace Graphics::Detail
{
    struct UniformTag {};

    template <typename Tag>
    class Int32Id
    {
    public:
        Int32Id()
            : value_(0)
        {}

        explicit Int32Id(const int32_t id)
            : value_(id)
        {}

        [[nodiscard]] GLint AsGlType() const { return static_cast<GLint>(value_); }

    private:
        int32_t value_;
    };
}
