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

        UpdateTiming();
        AnimateSides();
        UpdateSides();

        glLineWidth(3.0f);

        // Bindings
        glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);
        glBindVertexArray(m_VertexArrayID);

        // Draw
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, m_Window.ResolutionWidth(), m_Window.ResolutionHeight());
        
        glUseProgram(m_TriangleShaderID);
        glUniformMatrix4fv(m_TriangleProjMatrixUniformLocation, 1, GL_FALSE, &m_ProjectionMatrix[0][0]);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TriangleIndexBufferID);
        glDrawElements(GL_TRIANGLES, m_CircleModel->NumIndexes(), GL_UNSIGNED_INT, 0);

        glUseProgram(m_LineShaderID);
        glUniformMatrix4fv(m_LineProjMatrixUniformLocation, 1, GL_FALSE, &m_ProjectionMatrix[0][0]);
        glUniform4fv(m_LineColorUniformLocation, 1, &glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_LineIndexBufferID);
        glDrawElements(GL_LINES, m_NumLineIndexes, GL_UNSIGNED_INT, 0);

        // Release bindings
        glLineWidth(1.0f);
        glUseProgram(0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    namespace {

        // Helper to display a little (?) mark which shows a tooltip when hovered.
        static void HelpMarker(const char* desc)
        {
            ImGui::TextDisabled("(?)");
            if (ImGui::IsItemHovered())
            {
                ImGui::BeginTooltip();
                ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                ImGui::TextUnformatted(desc);
                ImGui::PopTextWrapPos();
                ImGui::EndTooltip();
            }
        }

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

        ImGui::Checkbox("Animation", &m_AnimationEnabled);
        ImGui::InputInt("Sides", &m_NextSides, 1, 5);

        if (m_NextSides > m_MaxSides)
        {
            m_NextSides = m_MaxSides;
        }
        if (m_NextSides < 3)
        {
            m_NextSides = 3;
        }

        ImGui::SameLine(); HelpMarker("CTRL + Click to enter value");
        ImGui::SliderFloat("Interval", &m_AnimationInterval, 0.0f, 1.0f);

        ImGui::End();
    }

    void CircleDemo::OnEvent(const Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<RenderTargetChangedEvent>(OnRenderTargetChange());
        dispatcher.Dispatch<AspectRatioChangeEvent>(OnAspectRatioChange());
    }

    EventHandler<RenderTargetChangedEvent> CircleDemo::OnRenderTargetChange()
    {
        return [this](const RenderTargetChangedEvent& event)
        {
            m_FrameBufferID = event.NextRenderTargetID();
        };
    }

    EventHandler<AspectRatioChangeEvent> CircleDemo::OnAspectRatioChange()
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

    void CircleDemo::UpdateTiming()
    {
        double nextTime = Timer::Get();
        m_DeltaTime = static_cast<float>(nextTime - m_LastTime);
        m_LastTime = nextTime;
        m_TimeSinceLastChange += m_DeltaTime;
    }

    void CircleDemo::UpdateSides()
    {
        if (m_NextSides == m_Sides)
            return;

        m_Sides = m_NextSides;
        m_CircleModel = std::make_unique<Circle>(m_Sides);

        const unsigned int bufferOffset = 0;

        const auto lineIndexes = m_CircleModel->MakeIndexesForLineDrawMode(m_Sides);
        const auto lineIndexByteSize = static_cast<unsigned int>(std::size(lineIndexes)) * sizeof(unsigned int);
        m_NumLineIndexes = static_cast<unsigned int>(std::size(lineIndexes));

        //Update vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferSubData(GL_ARRAY_BUFFER,
            bufferOffset,
            m_CircleModel->VertexDataByteSize(),
            &m_CircleModel->Vertexes[0]);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //Update index buffers
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TriangleIndexBufferID);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
            bufferOffset,
            m_CircleModel->IndexDataByteSize(),
            &m_CircleModel->Indexes[0]);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_LineIndexBufferID);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
            bufferOffset,
            lineIndexByteSize,
            &lineIndexes[0]);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void CircleDemo::AnimateSides()
    {
        if (!m_AnimationEnabled)
            return;

        if (m_TimeSinceLastChange > m_AnimationInterval)
        {
            m_TimeSinceLastChange = 0.0;

            if (m_SidesIncreasing)
            {
                if (m_Sides == m_MaxSides)
                {
                    m_SidesIncreasing = false;
                    --m_NextSides;
                }
                else
                {
                    ++m_NextSides;
                }
            }
            if (!m_SidesIncreasing)
            {
                if (m_Sides == 3)
                {
                    m_SidesIncreasing = true;
                    ++m_NextSides;
                }
                else
                {
                    --m_NextSides;
                }
            }
        }
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

        glGenBuffers(1, &m_TriangleIndexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_TriangleIndexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_CircleModel->IndexDataByteSize(), &m_CircleModel->Indexes[0], GL_STATIC_DRAW);

        const auto lineIndexes = m_CircleModel->MakeIndexesForLineDrawMode(m_Sides);
        const auto lineIndexByteSize = static_cast<unsigned int>(std::size(lineIndexes)) * sizeof(unsigned int);
        m_NumLineIndexes = static_cast<unsigned int>(std::size(lineIndexes));
        glGenBuffers(1, &m_LineIndexBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_LineIndexBufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, lineIndexByteSize, &lineIndexes[0], GL_STATIC_DRAW);

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

        m_TriangleShaderID = CreateShader("res/shaders/CircleDemo_TriangleVertex.shader", "res/shaders/CircleDemo_TriangleFragment.shader");
        m_TriangleProjMatrixUniformLocation = glGetUniformLocation(m_TriangleShaderID, "u_Proj");

        m_LineShaderID = CreateShader("res/shaders/CircleDemo_LineVertex.shader", "res/shaders/CircleDemo_LineFragment.shader");
        m_LineColorUniformLocation = glGetUniformLocation(m_LineShaderID, "u_LineColor");
        m_LineProjMatrixUniformLocation = glGetUniformLocation(m_LineShaderID, "u_Proj");

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

        glDeleteProgram(m_TriangleShaderID);
        glDeleteProgram(m_LineShaderID);
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
