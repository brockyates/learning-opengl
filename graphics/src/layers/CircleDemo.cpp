#include "pch.h"
#include "CircleDemo.h"

#include "events/EventDispatcher.h"

#include "imgui/ImGuiHelpers.h"

#include "logging/Log.h"

#include "models/Circle.h"

#include "renderer/ShaderHelpers.h"
#include "types/Timer.h"
#include "window/Window.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <utility>
#include <imgui.h>

namespace Graphics {

    CircleDemo::CircleDemo(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, std::move(eventCallback), "Circle Demo")
        , circleModel_(std::make_unique<Circle>(vertexCount_))
        , projectionMatrix_(glm::ortho(-1.0f * window_.AspectRatio(), 1.0f * window_.AspectRatio(), -1.0f, 1.0f))
        , lastTime_(Timer::Get())
    {}

    void CircleDemo::RenderScene()
    {
        if (!attached_)
            return;

        UpdateTiming();
        AnimateSides();
        UpdateSides();

        glLineWidth(1.0f);

        // Bindings
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId_);
        glBindVertexArray(vertexArrayId_);

        // Draw
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, window_.ResolutionWidth(), window_.ResolutionHeight());
        
        glUseProgram(triangleShaderId_);
        glUniformMatrix4fv(triangleProjMatrixUniformLocation_, 1, GL_FALSE, &projectionMatrix_[0][0]);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleIndexBufferId_);
        glDrawElements(GL_TRIANGLES, circleModel_->NumIndexes(), GL_UNSIGNED_INT, nullptr);

        glUseProgram(lineShaderId_);
        glUniformMatrix4fv(lineProjMatrixUniformLocation_, 1, GL_FALSE, &projectionMatrix_[0][0]);
        glUniform4fv(lineColorUniformLocation_, 1, &glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineIndexBufferId_);
        glDrawElements(GL_LINES, numLineIndexes_, GL_UNSIGNED_INT, nullptr);

        // Release bindings
        glLineWidth(1.0f);
        glUseProgram(0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void CircleDemo::RenderUi()
    {
        if (!attached_)
            return;

        ImGui::Begin("DemoWidget");

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::TextWrapped("%s", Description().c_str());
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();

        ImGui::Checkbox("Animation", &animationEnabled_);
        ImGui::InputInt("Vertex Count", &nextVertexes_, 1, 5);

        if (nextVertexes_ > MAX_VERTEXES)
        {
            nextVertexes_ = MAX_VERTEXES;
        }
        if (nextVertexes_ < 4)
        {
            nextVertexes_ = 4;
        }

        ImGui::SameLine(); HelpMarker("CTRL + Click to enter value");
        ImGui::SliderFloat("Interval", &animationInterval_, 0.0f, 1.0f);

        ImGui::End();
    }

    void CircleDemo::OnEvent(const Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<RenderTargetChangeEvent>(OnRenderTargetChange());
        dispatcher.Dispatch<AspectRatioChangeEvent>(OnAspectRatioChange());
    }

    EventHandler<RenderTargetChangeEvent> CircleDemo::OnRenderTargetChange()
    {
        return [this](const RenderTargetChangeEvent& event)
        {
            frameBufferId_ = event.NextRenderTargetId();
        };
    }

    EventHandler<AspectRatioChangeEvent> CircleDemo::OnAspectRatioChange()
    {
        return [this](const AspectRatioChangeEvent& event)
        {
            //Case: scene window's width < height
            if (event.NewAspectRatio() < 1.0f)
            {
                projectionMatrix_ = glm::ortho(-1.0f, 1.0f, -1.0f / window_.AspectRatio(), 1.0f / window_.AspectRatio());
                return;
            }

            //Case: scene window's width > height
            projectionMatrix_ = glm::ortho(-1.0f * window_.AspectRatio(), 1.0f * window_.AspectRatio(), -1.0f, 1.0f);
        };
    }

    void CircleDemo::UpdateTiming()
    {
        const auto nextTime = Timer::Get();
        deltaTime_ = static_cast<float>(nextTime - lastTime_);
        lastTime_ = nextTime;
        timeSinceLastChange_ += deltaTime_;
    }

    void CircleDemo::UpdateSides()
    {
        if (nextVertexes_ == vertexCount_)
            return;

        vertexCount_ = nextVertexes_;
        circleModel_ = std::make_unique<Circle>(vertexCount_);

        const unsigned int bufferOffset = 0;

        const auto lineIndexes = circleModel_->MakeIndexesForLineDrawMode(vertexCount_);
        const auto lineIndexByteSize = static_cast<unsigned int>(std::size(lineIndexes)) * sizeof(unsigned int);
        numLineIndexes_ = static_cast<unsigned int>(std::size(lineIndexes));

        //Update vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId_);
        glBufferSubData(GL_ARRAY_BUFFER,
            bufferOffset,
            circleModel_->VertexDataByteSize(),
            &circleModel_->Vertexes[0]);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //Update index buffers
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleIndexBufferId_);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
            bufferOffset,
            circleModel_->IndexDataByteSize(),
            &circleModel_->Indexes[0]);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineIndexBufferId_);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
            bufferOffset,
            lineIndexByteSize,
            &lineIndexes[0]);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void CircleDemo::AnimateSides()
    {
        if (!animationEnabled_)
            return;

        if (timeSinceLastChange_ > animationInterval_)
        {
            timeSinceLastChange_ = 0.0;

            if (sidesIncreasing_)
            {
                if (vertexCount_ == MAX_VERTEXES)
                {
                    sidesIncreasing_ = false;
                    --nextVertexes_;
                }
                else
                {
                    ++nextVertexes_;
                }
            }
            if (!sidesIncreasing_)
            {
                if (vertexCount_ == 4)
                {
                    sidesIncreasing_ = true;
                    ++nextVertexes_;
                }
                else
                {
                    --nextVertexes_;
                }
            }
        }
    }

    void CircleDemo::Attach()
    {
        if (attached_) return;

        LogTrace("Attaching CircleDemo");

        //Layer settings
        glEnable(GL_PROGRAM_POINT_SIZE);

        //Buffer setup
        glGenVertexArrays(1, &vertexArrayId_);
        glBindVertexArray(vertexArrayId_);
        glGenBuffers(1, &vertexBufferId_);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId_);
        glBufferData(GL_ARRAY_BUFFER, circleModel_->VertexDataByteSize(), &circleModel_->Vertexes[0], GL_STATIC_DRAW);

        glGenBuffers(1, &triangleIndexBufferId_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleIndexBufferId_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, circleModel_->IndexDataByteSize(), &circleModel_->Indexes[0], GL_STATIC_DRAW);

        const auto lineIndexes = circleModel_->MakeIndexesForLineDrawMode(vertexCount_);
        const auto lineIndexByteSize = static_cast<unsigned int>(std::size(lineIndexes)) * sizeof(unsigned int);
        numLineIndexes_ = static_cast<unsigned int>(std::size(lineIndexes));
        glGenBuffers(1, &lineIndexBufferId_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineIndexBufferId_);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, lineIndexByteSize, &lineIndexes[0], GL_STATIC_DRAW);

        //Vertex Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, Vertex1::ELEMENTS_PER_POSITION, Vertex1::POSITION_TYPE, GL_FALSE, Vertex1::VERTEX_BYTE_SIZE, reinterpret_cast<void*>(offsetof(Vertex1, Position)));

        //Vertex Color
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, Vertex1::ELEMENTS_PER_COLOR, Vertex1::COLOR_TYPE, GL_FALSE, Vertex1::VERTEX_BYTE_SIZE, reinterpret_cast<void*>(offsetof(Vertex1, Color)));

        //Release bindings
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        triangleShaderId_ = CreateShader("res/shaders/CircleDemo_TriangleVertex.shader", "res/shaders/CircleDemo_TriangleFragment.shader");
        triangleProjMatrixUniformLocation_ = glGetUniformLocation(triangleShaderId_, "u_Proj");

        lineShaderId_ = CreateShader("res/shaders/CircleDemo_LineVertex.shader", "res/shaders/CircleDemo_LineFragment.shader");
        lineColorUniformLocation_ = glGetUniformLocation(lineShaderId_, "u_LineColor");
        lineProjMatrixUniformLocation_ = glGetUniformLocation(lineShaderId_, "u_Proj");

        attached_ = true;
    }

    void CircleDemo::Detach()
    {
        if (!attached_) return;

        LogTrace("Detaching CircleDemo");

        glDisable(GL_PROGRAM_POINT_SIZE);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDeleteProgram(triangleShaderId_);
        glDeleteProgram(lineShaderId_);
        glDeleteBuffers(1, &vertexBufferId_);

        attached_ = false;
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
