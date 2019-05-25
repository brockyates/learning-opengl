#include "pch.h"
#include "CircleDemo.h"

#include "events/EventDispatcher.h"
#include "ShaderHelpers.h"
#include "WindowProperties.h"

#include <glad/glad.h>
#include <imgui.h>

namespace Graphics {

    CircleDemo::CircleDemo(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, eventCallback, "Circle Demo")
    {}

    void CircleDemo::RenderScene()
    {
        if (!m_Attached)
            return;

        // Bindings
        glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
        glBindVertexArray(m_VertexArrayID);
        glUseProgram(m_ShaderID);

        // Draw
        glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, m_Window.ResolutionWidth(), m_Window.ResolutionHeight());
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Release bindings
        glUseProgram(0);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void CircleDemo::RenderUI()
    {
        if (!m_Attached)
            return;

        ImGui::Begin("DemoWidget");

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::TextWrapped(Description().c_str());
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();

        ImGui::End();
    }

    void CircleDemo::OnEvent(const Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<RenderTargetChangedEvent>(OnRenderTargetChanged());
    }

    EventHandler<RenderTargetChangedEvent> CircleDemo::OnRenderTargetChanged()
    {
        return [this](const RenderTargetChangedEvent& event)
        {
            m_FrameBufferID = event.NextRenderTargetID();
        };
    }

    void CircleDemo::Attach()
    {
        if (m_Attached) return;

        LOG_TRACE("Attaching CircleDemo");

        glGenVertexArrays(1, &m_VertexArrayID);
        glBindVertexArray(m_VertexArrayID);
        glGenBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, std::size(m_Vertexes) * sizeof(float), &m_Vertexes[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

        //Release bindings
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        m_ShaderID = CreateShader("res/shaders/Minimal_Vertex.shader", "res/shaders/Minimal_Fragment.shader");

        m_Attached = true;
    }

    void CircleDemo::Detach()
    {
        if (!m_Attached) return;

        LOG_TRACE("Detaching CircleDemo");

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glDeleteProgram(m_ShaderID);
        glDeleteBuffers(1, &m_VertexBufferID);

        m_Attached = false;
    }

    std::string CircleDemo::PopupText() const
    {
        return "Draws circles.";
    }

    std::string CircleDemo::Description() const
    {
        return "Draw circles. Exposes controls to specify the number of vertices.";
    }

}
