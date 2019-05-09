#include "pch.h"
#include "MinimalRenderDemo.h"
#include "renderer/Shader.h"

#include <glad/glad.h>
#include <imgui.h>

namespace Graphics {

    MinimalRenderDemo::MinimalRenderDemo()
        : m_ShaderID(CreateShader("res/shaders/Minimal_Vertex.shader", "res/shaders/Minimal_Fragment.shader"))
    {
        glGenVertexArrays(1, &m_VertexArrayID);
        glBindVertexArray(1);
        glGenBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, std::size(m_Vertexes) * sizeof(float), &m_Vertexes[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }

    MinimalRenderDemo::~MinimalRenderDemo()
    {
        glDeleteProgram(m_ShaderID);
        glDeleteBuffers(1, &m_VertexBufferID);
    }

    void MinimalRenderDemo::OnRender()
    {
        if (!m_Enabled)
            return;

        glUseProgram(m_ShaderID);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(0);
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
