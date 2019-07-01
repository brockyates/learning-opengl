#include "pch.h"
#include "Vertex1.h"

#include <glad/glad.h>

namespace Graphics
{
    // ReSharper disable CppRedundantParentheses
    const size_t Vertex1::VERTEX_BYTE_SIZE = sizeof(Position) + sizeof(Color);

    const int Vertex1::ELEMENTS_PER_POSITION = sizeof(Position) / sizeof(float);
    const unsigned int Vertex1::POSITION_TYPE = GL_FLOAT;

    const int Vertex1::ELEMENTS_PER_COLOR = sizeof(Color) / sizeof(float);
    const unsigned int Vertex1::COLOR_TYPE = GL_FLOAT;
    // ReSharper restore CppRedundantParentheses
}
