#include "pch.h"
#include "MinimalRenderDemo.h"
#include "renderer/Shader.h"

#include <glad/glad.h>
#include <imgui.h>

namespace Graphics {

    MinimalRenderDemo::MinimalRenderDemo()
        : m_Shader("res/shaders/Minimal_Vertex.shader", "res/shaders/Minimal_Fragment.shader")
    {
        glGenBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, std::size(m_Vertexes) * sizeof(float), &m_Vertexes[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    MinimalRenderDemo::~MinimalRenderDemo()
    {
        glDeleteBuffers(1, &m_VertexBufferID);
    }

    void MinimalRenderDemo::OnRender()
    {
        if (!m_Enabled)
            return;

        m_Shader.Bind();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        m_Shader.Unbind();
    }

    void MinimalRenderDemo::OnImGuiRender()
    {
        ImGui::Begin("Demo");
            if (ImGui::CollapsingHeader("Minimal Render"))
            {
                ImGui::Checkbox("Enabled", &m_Enabled);
            }
        ImGui::End();
    }

}