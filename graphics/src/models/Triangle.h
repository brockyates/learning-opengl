#pragma once

#include "Model.h"

namespace Graphics
{
    struct Triangle final : Model
    {
        Triangle();

    private:
        static constexpr float Y_OFFSET = 0.866f; //To produce equilateral triangle centered in scene
    };
}
