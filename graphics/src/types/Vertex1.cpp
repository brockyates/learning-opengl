#include "pch.h"
#include "Vertex1.h"

#include <glad/glad.h>

namespace Graphics {

    const unsigned int Vertex1::VertexByteSize = sizeof(Position);

    const unsigned int Vertex1::ElementsPerPosition = sizeof(Position) / sizeof(float);
    const unsigned int Vertex1::PositionType = GL_FLOAT;

}
