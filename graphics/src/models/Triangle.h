#pragma once

#include "Model.h"
#include "types/Vertex1.h"

#include <glm/glm.hpp>

#include <vector>

namespace Graphics {

    struct Triangle : public Model
    {
    public:
        Triangle()
            : Model({
                {
                    glm::vec4{ 0.0f,  1.0f, 0.0f, 1.0f }, //Position
                    glm::vec4{ 1.0f,  0.0f, 0.0f, 1.0f }, //Color
                },
                {
                    glm::vec4{ 1.0f, -1.0f, 0.0f, 1.0f },
                    glm::vec4{ 0.0f,  1.0f, 0.0f, 1.0f },
                },
                {
                    glm::vec4{-1.0f, -1.0f, 0.0f, 1.0f },
                    glm::vec4{ 0.0f,  0.0f, 1.0f, 1.0f },
                }
            })
        {}
    };

}
