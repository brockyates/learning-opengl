#pragma once

#include "Model.h"

namespace graphics {

    struct Triangle : public Model
    {
    public:
        Triangle();

    private:
        static constexpr float yOffset = 0.866f; //To produce equilateral triangle centered in scene
    };

}
