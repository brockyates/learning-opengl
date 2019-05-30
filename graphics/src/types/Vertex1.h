#pragma once

#include <glm/glm.hpp>

namespace graphics {

    struct Vertex1
    {
        Vertex1(glm::vec4 position, glm::vec4 color)
            : Position(position)
            , Color(color)
        {}

        glm::vec4 Position;
        glm::vec4 Color;

        static const unsigned int VertexByteSize;

        static const unsigned int ElementsPerPosition;
        static const unsigned int PositionType;

        static const unsigned int ElementsPerColor;
        static const unsigned int ColorType;

    };

}
