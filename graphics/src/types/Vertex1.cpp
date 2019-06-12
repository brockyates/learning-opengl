#include "pch.h"
#include "Vertex1.h"

#include <glad/glad.h>

namespace Graphics
{
    const uint32_t Vertex1::VERTEX_BYTE_SIZE = sizeof Position + sizeof Color;

    const uint32_t Vertex1::ELEMENTS_PER_POSITION = sizeof Position / sizeof(float);
    const uint32_t Vertex1::POSITION_TYPE = GL_FLOAT;

    const uint32_t Vertex1::ELEMENTS_PER_COLOR = sizeof Color / sizeof(float);
    const uint32_t Vertex1::COLOR_TYPE = GL_FLOAT;
}
