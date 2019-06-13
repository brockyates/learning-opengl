#pragma once

#include <glad/glad.h>

namespace Graphics::Detail
{
    struct UniformTag {};

    template <typename Tag>
    class IntId
    {
    public:
        IntId()
            : value_(0)
        {}

        explicit IntId(const int id)
            : value_(id)
        {}

        [[nodiscard]] GLint AsGlType() const { return static_cast<GLint>(value_); }

    private:
        int value_;
    };
}
