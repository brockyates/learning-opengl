#include "pch.h"
#include "Triangle.h"

#include <glm/glm.hpp>

namespace Graphics
{
    Triangle::Triangle()
        : Model(
            {
                {
                    glm::vec4{  0.0f,  Y_OFFSET, 0.0f, 1.0f }, //Position
                    glm::vec4{  1.0f,  0.0f,    0.0f, 1.0f }, //Color
                },
                {
                    glm::vec4{  1.0f, -Y_OFFSET, 0.0f, 1.0f },
                    glm::vec4{  0.0f,  1.0f,    0.0f, 1.0f },
                },
                {
                    glm::vec4{ -1.0f, -Y_OFFSET, 0.0f, 1.0f },
                    glm::vec4{  0.0f,  0.0f,    1.0f, 1.0f },
                } //Vertex data
            },
            { 0, 1, 2 } //Index data
        )
        {}
}
