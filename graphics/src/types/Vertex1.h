#pragma once

#include <glm/glm.hpp>

namespace Graphics
{
    struct Vertex1
    {
        Vertex1(const glm::vec4 position, const glm::vec4 color)
            : Position(position)
            , Color(color)
        {}

        glm::vec4 Position;
        glm::vec4 Color;

        static const size_t VERTEX_BYTE_SIZE;

        static const int ELEMENTS_PER_POSITION;
        static const unsigned int POSITION_TYPE;

        static const int ELEMENTS_PER_COLOR;
        static const unsigned int COLOR_TYPE;

    };
}
