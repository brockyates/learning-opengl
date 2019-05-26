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
        glUniform1f(m_PointsizeUniformLocation, 30.0f);

        // Draw
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, m_Window.ResolutionWidth(), m_Window.ResolutionHeight());
        glDrawElements(GL_TRIANGLES, m_CircleModel->NumIndexes(), GL_UNSIGNED_INT, 0);

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

        //Layer settings
        glEnable(GL_PROGRAM_POINT_SIZE);

        //Buffer setup
        glGenVertexArrays(1, &m_VertexArrayID);
        glBindVertexArray(m_VertexArrayID);
        glGenBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, m_CircleModel->VertexDataByteSize(), &m_CircleModel->Vertexes[0], GL_STATIC_DRAW);

        glGenBuffers(1, &m_IndexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_CircleModel->IndexDataByteSize(), &m_CircleModel->Indexes[0], GL_STATIC_DRAW);

        //Vertex Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, Vertex1::ElementsPerPosition, Vertex1::PositionType, GL_FALSE, Vertex1::VertexByteSize, reinterpret_cast<void*>(offsetof(Vertex1, Position)));

        //Vertex Color
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, Vertex1::ElementsPerColor, Vertex1::ColorType, GL_FALSE, Vertex1::VertexByteSize, reinterpret_cast<void*>(offsetof(Vertex1, Color)));

        //Release bindings
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        m_ShaderID = CreateShader("res/shaders/CircleDemo_Vertex.shader", "res/shaders/CircleDemo_Fragment.shader");
        m_PointsizeUniformLocation = glGetUniformLocation(m_ShaderID, "u_Pointsize");

        m_Attached = true;
    }

    void CircleDemo::Detach()
    {
        if (!m_Attached) return;

        LOG_TRACE("Detaching CircleDemo");

        glDisable(GL_PROGRAM_POINT_SIZE);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
