#include "pch.h"
#include "Vertex1.h"

#include <glad/glad.h>

namespace Graphics {

    const unsigned int Vertex1::VertexByteSize = sizeof(Position) + sizeof(Color);

    const unsigned int Vertex1::ElementsPerPosition = sizeof(Position) / sizeof(float);
    const unsigned int Vertex1::PositionType = GL_FLOAT;

    const unsigned int Vertex1::ElementsPerColor = sizeof(Color) / sizeof(float);
    const unsigned int Vertex1::ColorType = GL_FLOAT;

}
