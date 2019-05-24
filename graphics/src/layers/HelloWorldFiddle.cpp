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

        UpdateTiming();
        UpdateVertexes();

        glLineWidth(m_LineWidth);

        // Bindings
        glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
        glBindVertexArray(m_VertexArrayID);
        glUseProgram(m_ShaderID);
        glUniform1f(m_PointsizeUniformLocation, m_PointSize);

        // Draw
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, m_Window.ResolutionWidth(), m_Window.ResolutionHeight());
        glDrawElements(m_DrawMode.Mode, m_DrawMode.NumVertexes, GL_UNSIGNED_INT, 0);

        // Release bindings
        glLineWidth(1.0f);
        glUseProgram(0);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void HelloWorldFiddle::UpdateVertexes()
    {
        if (m_AnimationEnabled)
        {
            SetNextVertexPositions();
        }

        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);

        const unsigned int bufferOffset = 0;
        glBufferSubData(GL_ARRAY_BUFFER,
            bufferOffset,
            m_TriangleModel->VertexDataByteSize(),
            &m_TriangleModel->Vertexes[0]);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void HelloWorldFiddle::UpdateTiming()
    {
        double nextTime = Time::Get();
        m_DeltaTime = static_cast<float>(nextTime - m_LastTime);
        m_LastTime = nextTime;
    }

    void HelloWorldFiddle::SetNextVertexPositions()
    {
        auto m_VertexYPos = m_TriangleModel->Vertexes[0].Position[1];

        if (m_VertexYDirection == 1)
        {
            m_VertexYPos += m_VertexMoveSpeed * static_cast<float>(m_DeltaTime);
            if (m_TriangleModel->Vertexes[0].Position[1] >= 1.0f)
            {
                m_VertexYDirection = 0;
            }
        }
        else
        {
            m_VertexYPos -= m_VertexMoveSpeed * static_cast<float>(m_DeltaTime);
            if (m_TriangleModel->Vertexes[0].Position[1] <= -1.0f)
            {
                m_VertexYDirection = 1;
            }
        }

        m_TriangleModel->Vertexes[0].Position[1] = m_VertexYPos;
    }

    void HelloWorldFiddle::ChangeDrawMode(const DrawMode& nextMode)
    {
        m_DrawMode = nextMode;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);

        const unsigned int bufferOffset = 0;
        if (nextMode.Mode == GL_LINES)
        {
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
                bufferOffset,
                std::size(m_LineIndexes) * sizeof(unsigned int),
                &m_LineIndexes[0]);
        }
        else
        {
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
                bufferOffset,
                m_TriangleModel->IndexDataByteSize(),
                &m_TriangleModel->Indexes[0]);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void HelloWorldFiddle::RenderUI()
    {
        if (!m_Attached)
            return;

        ImGui::Begin("DemoWidget");

        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::TextWrapped(Description().c_str());
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        if (ImGui::BeginCombo("Draw Mode", m_DrawMode.DisplayName.c_str()))
        {
            for (const auto& mode : m_DrawModes)
            {
                bool isSelected = (m_DrawMode.Mode == mode.first);

                if (ImGui::Selectable(mode.second.DisplayName.c_str(), isSelected))
                {
                    ChangeDrawMode(mode.second);
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Color Controls");
        ImGui::Separator();
        ImGui::ColorEdit4("glClearColor", &m_ClearColor[0]);
        ImGui::ColorEdit4("Vertex 1", &m_TriangleModel->Vertexes[0].Color[0]);
        ImGui::ColorEdit4("Vertex 2", &m_TriangleModel->Vertexes[1].Color[0]);
        ImGui::ColorEdit4("Vertex 3", &m_TriangleModel->Vertexes[2].Color[0]);

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Position Controls");
        ImGui::Separator();

        /*
        SliderFloat2 takes the address of an array of two floats as the second argument.
        Position is an array of 4 floats, but this works because SliderFloat2 only requires that it can index 2 elements in the array.
        */
        ImGui::SliderFloat2("Vertex 1", &m_TriangleModel->Vertexes[0].Position[0], -1.0f, 1.0f);
        ImGui::SliderFloat2("Vertex 2", &m_TriangleModel->Vertexes[1].Position[0], -1.0f, 1.0f);
        ImGui::SliderFloat2("Vertex 3", &m_TriangleModel->Vertexes[2].Position[0], -1.0f, 1.0f);

        if (m_DrawMode.Mode == GL_LINES)
        {
            ImGui::Dummy(ImVec2(0.0f, 20.0f));
            ImGui::Text("Line Controls");
            ImGui::Separator();
            ImGui::SliderFloat("Line Width", &m_LineWidth, 1.0f, 10.0f);
        }
        if (m_DrawMode.Mode == GL_POINTS)
        {
            ImGui::Dummy(ImVec2(0.0f, 20.0f));
            ImGui::Text("Point Controls");
            ImGui::Separator();
            ImGui::SliderFloat("Point Size", &m_PointSize, 1.0f, 100.0f);
        }

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

        //Layer settings
        glEnable(GL_PROGRAM_POINT_SIZE);
        glLineWidth(m_LineWidth);

        //Buffer setup
        glGenVertexArrays(1, &m_VertexArrayID);
        glBindVertexArray(m_VertexArrayID);
        glGenBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, m_TriangleModel->VertexDataByteSize(), &m_TriangleModel->Vertexes[0], GL_STATIC_DRAW);

        glGenBuffers(1, &m_IndexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);

        //Allocate a buffer that can hold the larger of the two index buffers, in this case the line indexes are larger than the triangle indexes.
        const auto indexBufferByteSize = std::size(m_LineIndexes) * sizeof(unsigned int);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferByteSize, &m_TriangleModel->Indexes[0], GL_STATIC_DRAW);

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
        m_PointsizeUniformLocation = glGetUniformLocation(m_ShaderID, "u_Pointsize");

        m_Attached = true;
    }

    void HelloWorldFiddle::Detach()
    {
        if (!m_Attached) return;

        LOG_TRACE("Detaching HelloWorldFiddle");

        glDisable(GL_PROGRAM_POINT_SIZE);
        glLineWidth(1.0f);

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
        return "Very basic demo that allows you to fiddle with color, vertex position, and draw mode.";
    }

}
