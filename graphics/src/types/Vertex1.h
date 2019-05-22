#pragma once

#include <glm/glm.hpp>

namespace Graphics {

    struct Vertex1
    {
        Vertex1(glm::vec4 position)
            : Position(position)
        {}

        glm::vec4 Position;

        static const unsigned int VertexByteSize;

        static const unsigned int ElementsPerPosition;
        static const unsigned int PositionType;

    };

}
