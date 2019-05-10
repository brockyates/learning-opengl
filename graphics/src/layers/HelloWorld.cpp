#include "pch.h"
#include "HelloWorld.h"
#include "ShaderHelpers.h"

#include <glad/glad.h>
#include <imgui.h>

namespace Graphics {

    HelloWorld::HelloWorld()
        : Layer("Hello World")
    {}

    void HelloWorld::OnUpdate()
    {
        if (!m_Attached)
            return;

        glUseProgram(m_ShaderID);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(0);
    }

    void HelloWorld::OnImGuiRender()
    {
        if (!m_Attached)
            return;

        ImGui::Begin("Demos");

        ImGui::Spacing();
        ImGui::TextWrapped(GetDescription().c_str());

        ImGui::End();
    }

    void HelloWorld::Attach()
    {
        if (m_Attached) return;

        LOG_TRACE("Attaching HelloWorld");

        m_ShaderID = CreateShader("res/shaders/Minimal_Vertex.shader", "res/shaders/Minimal_Fragment.shader");

        glGenVertexArrays(1, &m_VertexArrayID);
        glBindVertexArray(m_VertexArrayID);
        glGenBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, std::size(m_Vertexes) * sizeof(float), &m_Vertexes[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

        m_Attached = true;
    }

    void HelloWorld::Detach()
    {
        if (!m_Attached) return;

        LOG_TRACE("Detaching HelloWorld");

        glDeleteProgram(m_ShaderID);
        glDeleteBuffers(1, &m_VertexBufferID);

        m_Attached = false;
    }

    std::string HelloWorld::GetPopupText() const
    {
        return "Draws triangle on minimal window";
    }

    std::string HelloWorld::GetDescription() const
    {
        return "Hello World is a minimal demo. Draws a triangle on the window, and exposes no UI controls.";
    }

}
