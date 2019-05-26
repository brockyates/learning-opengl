#include "pch.h"
#include "Circle.h"

namespace Graphics {

    Circle::Circle()
        : Model(MakeVertexes(), MakeIndexes())
    {}

    std::vector<Vertex1> Circle::MakeVertexes() const
    {
        return
        {
            {
                glm::vec4{ 0.0f,  0.0f, 0.0f, 1.0f }, //Position
                glm::vec4{ 1.0f,  1.0f, 1.0f, 1.0f }, //Color
            },
            {
                glm::vec4{ 0.0f,  1.0f, 0.0f, 1.0f },
                glm::vec4{ 1.0f,  0.0f, 0.0f, 1.0f },
            },
            {
                glm::vec4{ 1.0f, -1.0f, 0.0f, 1.0f },
                glm::vec4{ 0.0f,  1.0f, 0.0f, 1.0f },
            },
            {
                glm::vec4{-1.0f, -1.0f, 0.0f, 1.0f },
                glm::vec4{ 0.0f,  0.0f, 1.0f, 1.0f },
            }
        };
    }

    std::vector<unsigned int> Circle::MakeIndexes() const
    {
        return
        {
            {
                2, 0, 1,
                3, 0, 2,
                1, 0, 3,
            }
        };
    }

}
