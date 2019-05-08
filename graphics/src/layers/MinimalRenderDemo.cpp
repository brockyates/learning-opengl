#include "pch.h"
#include "MinimalRenderDemo.h"
#include "renderer/Shader.h"

#include <glad/glad.h>
#include <imgui.h>

namespace Graphics {

    MinimalRenderDemo::MinimalRenderDemo()
        : m_Shader("res/shaders/Minimal_Vertex.shader", "res/shaders/Minimal_Fragment.shader")
    {
        GLCall(glGenBuffers(1, &m_VertexBufferID));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID));
        GLCall(glBufferData(GL_ARRAY_BUFFER, std::size(m_Vertexes) * sizeof(float), &m_Vertexes[0], GL_STATIC_DRAW));
        GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
    }

    MinimalRenderDemo::~MinimalRenderDemo()
    {
        GLCall(glDeleteBuffers(1, &m_VertexBufferID));
    }

    void MinimalRenderDemo::OnRender()
    {
        if (!m_Enabled)
            return;

        m_Shader.Bind();

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));

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
