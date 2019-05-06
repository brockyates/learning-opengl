#include "pch.h"
#include "MinimalTriangleDemo.h"
#include "renderer/Shader.h"

#include <glad/glad.h>

namespace Graphics {

    MinimalTriangleDemo::MinimalTriangleDemo()
        : m_Shader("res/shaders/Minimal_Vertex.shader", "res/shaders/Minimal_Fragment.shader")
    {
        glGenBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertexes), &m_Vertexes, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    void MinimalTriangleDemo::OnRender()
    {
        m_Shader.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

}
