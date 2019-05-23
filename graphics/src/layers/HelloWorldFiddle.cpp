#include "pch.h"
#include "HelloWorldFiddle.h"

#include "events/EventDispatcher.h"
#include "ShaderHelpers.h"
#include "WindowProperties.h"

#include <glad/glad.h>
#include <imgui.h>

namespace Graphics {

    HelloWorldFiddle::HelloWorldFiddle(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, eventCallback, "Hello World Fiddle")
    {}

    void HelloWorldFiddle::RenderScene()
    {
        if (!m_Attached)
            return;

        UpdateVertexes();

        // Bindings
        glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
        glBindVertexArray(m_VertexArrayID);
        glUseProgram(m_ShaderID);

        // Draw
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, m_Window.ResolutionWidth(), m_Window.ResolutionHeight());
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // Release bindings
        glUseProgram(0);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void HelloWorldFiddle::UpdateVertexes()
    {
        m_Vertexes[0].Color = m_Vertex1Color;
        m_Vertexes[1].Color = m_Vertex2Color;
        m_Vertexes[2].Color = m_Vertex3Color;

        m_Vertexes[0].Position = { m_Vertex1Pos[0], m_Vertex1Pos[1], 0.0f, 1.0f };
        m_Vertexes[1].Position = { m_Vertex2Pos[0], m_Vertex2Pos[1], 0.0f, 1.0f };
        m_Vertexes[2].Position = { m_Vertex3Pos[0], m_Vertex3Pos[1], 0.0f, 1.0f };

        unsigned int bufferOffset = 0;

        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);

        glBufferSubData(GL_ARRAY_BUFFER,
            bufferOffset,
            std::size(m_Vertexes) * Vertex1::VertexByteSize,
            &m_Vertexes[0]);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void HelloWorldFiddle::RenderUI()
    {
        if (!m_Attached)
            return;

        ImGui::Begin("DemoWidget");

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::TextWrapped(Description().c_str());

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Color Controls");
        ImGui::Separator();
        ImGui::ColorEdit4("glClearColor", &m_ClearColor[0]);
        ImGui::ColorEdit4("Vertex 1", &m_Vertex1Color[0]);
        ImGui::ColorEdit4("Vertex 2", &m_Vertex2Color[0]);
        ImGui::ColorEdit4("Vertex 3", &m_Vertex3Color[0]);

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Position Controls");
        ImGui::Separator();
        ImGui::SliderFloat2("Vertex 1", &m_Vertex1Pos[0], -1.0f, 1.0f);
        ImGui::SliderFloat2("Vertex 2", &m_Vertex2Pos[0], -1.0f, 1.0f);
        ImGui::SliderFloat2("Vertex 3", &m_Vertex3Pos[0], -1.0f, 1.0f);

        ImGui::End();
    }

    void HelloWorldFiddle::OnEvent(const Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<RenderTargetChangedEvent>(OnRenderTargetChanged());
    }

    EventHandler<RenderTargetChangedEvent> HelloWorldFiddle::OnRenderTargetChanged()
    {
        return [this](const RenderTargetChangedEvent& event)
        {
            m_FrameBufferID = event.NextRenderTargetID();
        };
    }

    void HelloWorldFiddle::Attach()
    {
        if (m_Attached) return;

        LOG_TRACE("Attaching HelloWorldFiddle");

        glGenVertexArrays(1, &m_VertexArrayID);
        glBindVertexArray(m_VertexArrayID);
        glGenBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, std::size(m_Vertexes) * (Vertex1::VertexByteSize), &m_Vertexes[0], GL_STATIC_DRAW);

        glGenBuffers(1, &m_IndexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_TriangleIndexes), &m_TriangleIndexes[0], GL_STATIC_DRAW);

        //Vertex Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, Vertex1::ElementsPerPosition, Vertex1::PositionType, GL_FALSE, Vertex1::VertexByteSize, reinterpret_cast<void*>(offsetof(Vertex1, Position)));

        //Vertex Color
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, Vertex1::ElementsPerColor, Vertex1::ColorType, GL_FALSE, Vertex1::VertexByteSize, reinterpret_cast<void*>(offsetof(Vertex1, Color)));

        //Release Bindings
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        m_ShaderID = CreateShader("res/shaders/HelloWorldFiddle_Vertex.shader", "res/shaders/HelloWorldFiddle_Fragment.shader");

        m_Attached = true;
    }

    void HelloWorldFiddle::Detach()
    {
        if (!m_Attached) return;

        LOG_TRACE("Detaching HelloWorldFiddle");

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glDeleteProgram(m_ShaderID);
        glDeleteBuffers(1, &m_VertexBufferID);

        m_Attached = false;
    }

    std::string HelloWorldFiddle::PopupText() const
    {
        return "Hello World, but with some UI controls";
    }

    std::string HelloWorldFiddle::Description() const
    {
        return "Very basic demo that allows you to fiddle with color and vertex position.";
    }

}
