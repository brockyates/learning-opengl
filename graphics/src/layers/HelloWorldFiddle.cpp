#include "pch.h"
#include "HelloWorldFiddle.h"
#include "ShaderHelpers.h"

#include "WindowProperties.h"

#include <glad/glad.h>
#include <imgui.h>

namespace Graphics {

    HelloWorldFiddle::HelloWorldFiddle(const WindowProperties& windowProperties)
        : m_WindowProperties(windowProperties)
        , Layer("Hello World Fiddle")
    {}

    void HelloWorldFiddle::OnUpdate()
    {
        if (!m_Attached)
            return;

        glUseProgram(m_ShaderID);

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
        glViewport(0, 0, m_WindowProperties.Width, m_WindowProperties.Height);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(0);
    }

    void HelloWorldFiddle::OnImGuiRender()
    {
        if (!m_Attached) return;

        ImGui::Begin("Demos");

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::TextWrapped(GetDescription().c_str());
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();
        ImGui::ColorEdit4("glClearColor", &m_ClearColor[0]);

        ImGui::End();
    }

    void HelloWorldFiddle::Attach()
    {
        if (m_Attached) return;

        LOG_TRACE("Attaching HelloWorldFiddle");

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

    void HelloWorldFiddle::Detach()
    {
        if (!m_Attached) return;

        LOG_TRACE("Detaching HelloWorldFiddle");

        glDeleteProgram(m_ShaderID);
        glDeleteBuffers(1, &m_VertexBufferID);

        m_Attached = false;
    }

    std::string HelloWorldFiddle::GetPopupText() const
    {
        return "Hello World, but with some UI controls";
    }

    std::string HelloWorldFiddle::GetDescription() const
    {
        return "Very basic demo that allows you to fiddle with simple parameters like color, vertex position, and draw mode.";
    }

}
