#include "pch.h"
#include "HelloWorldFiddle.h"

#include "events/EventDispatcher.h"

#include "logging/Log.h"

#include "ModelGenerator.h"
#include "ShaderHelpers.h"
#include "Timer.h"
#include "Window.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

#include <random>

namespace graphics {

    HelloWorldFiddle::HelloWorldFiddle(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, eventCallback, "Hello World Fiddle")
        , m_LastTime(Timer::Get())
        , m_TriangleModel(ModelGenerator::MakeTriangle())
        , m_DrawModes({
            { GL_TRIANGLES, {GL_TRIANGLES, 3, "Triangles" }},
            { GL_LINES,     {GL_LINES,     6, "Lines"     }},
            { GL_POINTS,    {GL_POINTS,    3, "Points"    }}
            })
        , m_DrawMode(m_DrawModes[GL_TRIANGLES])
        , m_ProjectionMatrix(glm::ortho(-1.0f * m_Window.AspectRatio(), 1.0f * m_Window.AspectRatio(), -1.0f, 1.0f))
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
        glUniformMatrix4fv(m_ProjMatrixUniformLocation, 1, GL_FALSE, &m_ProjectionMatrix[0][0]);

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

    void HelloWorldFiddle::UpdateVertex(glm::vec4& vertex, glm::vec4& direction)
    {
        const auto velocity= m_VertexMoveSpeed * direction;

        vertex += static_cast<float>(m_DeltaTime) * velocity;

        if (vertex.x < -1.0f)
        {
            vertex.x = -1.0f;
            direction.x *= -1.0f;
        }
        else if (vertex.x > 1.0f)
        {
            vertex.x = 1.0f;
            direction.x *= -1.0f;
        }

        if (vertex.y < -1.0f)
        {
            vertex.y = -1.0f;
            direction.y *= -1.0f;
        }
        else if (vertex.y > 1.0f)
        {
            vertex.y = 1.0f;
            direction.y *= -1.0f;
        }
    }

    void HelloWorldFiddle::UpdateTiming()
    {
        double nextTime = Timer::Get();
        m_DeltaTime = static_cast<float>(nextTime - m_LastTime);
        m_LastTime = nextTime;
    }

    void HelloWorldFiddle::SetNextVertexPositions()
    {
        UpdateVertex(m_TriangleModel->Vertexes[0].Position, m_Vertex1Direction);
        UpdateVertex(m_TriangleModel->Vertexes[1].Position, m_Vertex2Direction);
        UpdateVertex(m_TriangleModel->Vertexes[2].Position, m_Vertex3Direction);
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

    glm::vec4 HelloWorldFiddle::GetRandomVertexDirection() const
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_real_distribution<> dist(-1.0f, 1.0f);

        return { dist(rng), dist(rng), 0.0f, 0.0f };
    }

    void HelloWorldFiddle::DrawDescription() const
    {
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::TextWrapped(Description().c_str());
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();
    }

    void HelloWorldFiddle::DrawModeSelector()
    {
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
    }

    void HelloWorldFiddle::DrawColorControls()
    {
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Color Controls");
        ImGui::Separator();
        ImGui::ColorEdit4("glClearColor", &m_ClearColor[0]);
        ImGui::ColorEdit4("Vertex 1", &m_TriangleModel->Vertexes[0].Color[0]);
        ImGui::ColorEdit4("Vertex 2", &m_TriangleModel->Vertexes[1].Color[0]);
        ImGui::ColorEdit4("Vertex 3", &m_TriangleModel->Vertexes[2].Color[0]);
    }

    void HelloWorldFiddle::DrawPositionControls()
    {
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Position Controls");
        ImGui::Separator();
        if (ImGui::Button("Reset"))
        {
            m_AnimationEnabled = false;
            m_TriangleModel->Vertexes[0].Position = { 0.0f,  1.0f, 0.0f, 1.0f };
            m_TriangleModel->Vertexes[1].Position = { 1.0f, -1.0f, 0.0f, 1.0f };
            m_TriangleModel->Vertexes[2].Position = { -1.0f, -1.0f, 0.0f, 1.0f };
            m_Vertex1Direction = GetRandomVertexDirection();
            m_Vertex2Direction = GetRandomVertexDirection();
            m_Vertex3Direction = GetRandomVertexDirection();
        }

        /*
        SliderFloat2 takes the address of an array of two floats as the second argument.
        Position is an array of 4 floats, but this works because SliderFloat2 only requires that it can index 2 elements in the array.
        */
        ImGui::SliderFloat2("Vertex 1", &m_TriangleModel->Vertexes[0].Position[0], -1.0f, 1.0f);
        ImGui::SliderFloat2("Vertex 2", &m_TriangleModel->Vertexes[1].Position[0], -1.0f, 1.0f);
        ImGui::SliderFloat2("Vertex 3", &m_TriangleModel->Vertexes[2].Position[0], -1.0f, 1.0f);
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Checkbox("Animation", &m_AnimationEnabled);
        ImGui::SliderFloat("Speed", &m_VertexMoveSpeed, 0.0f, 5.0f);
    }

    void HelloWorldFiddle::DrawLineControls()
    {
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Line Controls");
        ImGui::Separator();
        ImGui::SliderFloat("Line Width", &m_LineWidth, 1.0f, 10.0f);
    }

    void HelloWorldFiddle::DrawPointControls()
    {
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Point Controls");
        ImGui::Separator();
        ImGui::SliderFloat("Point Size", &m_PointSize, 1.0f, 100.0f);
    }

    void HelloWorldFiddle::RenderUI()
    {
        if (!m_Attached)
            return;

        ImGui::Begin("DemoWidget");

        DrawDescription();
        DrawModeSelector();
        DrawColorControls();
        DrawPositionControls();

        if (m_DrawMode.Mode == GL_LINES)
        {
            DrawLineControls();
        }
        if (m_DrawMode.Mode == GL_POINTS)
        {
            DrawPointControls();
        }

        ImGui::End();
    }

    void HelloWorldFiddle::OnEvent(const Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<RenderTargetChangeEvent>(OnRenderTargetChanged());
        dispatcher.Dispatch<AspectRatioChangeEvent>(OnAspectRatioChange());
    }

    EventHandler<RenderTargetChangeEvent> HelloWorldFiddle::OnRenderTargetChanged()
    {
        return [this](const RenderTargetChangeEvent& event)
        {
            m_FrameBufferID = event.NextRenderTargetID();
        };
    }

    EventHandler<AspectRatioChangeEvent> HelloWorldFiddle::OnAspectRatioChange()
    {
        return [this](const AspectRatioChangeEvent& event)
        {
            //Case: scene window's width < height
            if (event.NewAspectRatio() < 1.0f)
            {
                m_ProjectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f / m_Window.AspectRatio(), 1.0f / m_Window.AspectRatio());
                return;
            }

            //Case: scene window's width > height
            m_ProjectionMatrix = glm::ortho(-1.0f * m_Window.AspectRatio(), 1.0f * m_Window.AspectRatio(), -1.0f, 1.0f);
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
        m_ProjMatrixUniformLocation = glGetUniformLocation(m_ShaderID, "u_Proj");

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
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
