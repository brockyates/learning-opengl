#include "pch.h"
#include "HelloWorldFiddle.h"

#include "events/EventDispatcher.h"

#include "logging/Log.h"

#include "models/ModelGenerator.h"
#include "renderer/ShaderHelpers.h"
#include "types/Timer.h"
#include "window/Window.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

#include <random>
#include <utility>

namespace Graphics {

    HelloWorldFiddle::HelloWorldFiddle(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, std::move(eventCallback), "Hello World Fiddle")
        , lastTime_(Timer::Get())
        , drawModes_({
            { GL_TRIANGLES, {GL_TRIANGLES, 3, "Triangles" }},
            { GL_LINES,     {GL_LINES,     6, "Lines"     }},
            { GL_POINTS,    {GL_POINTS,    3, "Points"    }}
        })
        , drawMode_(drawModes_[GL_TRIANGLES])
        , triangleModel_(ModelGenerator::MakeTriangle())
        , projectionMatrix_(glm::ortho(-1.0f * window_.AspectRatio(), 1.0f * window_.AspectRatio(), -1.0f, 1.0f))
    {}

    void HelloWorldFiddle::RenderScene()
    {
        if (!attached_)
            return;

        UpdateTiming();
        UpdateVertexes();

        glLineWidth(lineWidth_);

        // Bindings
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId_);
        glBindVertexArray(vertexArrayId_);
        glUseProgram(shaderId_);
        glUniform1f(pointSizeUniformLocation_, pointSize_);
        glUniformMatrix4fv(projMatrixUniformLocation_, 1, GL_FALSE, &projectionMatrix_[0][0]);

        // Draw
        glClearColor(clearColor_[0], clearColor_[1], clearColor_[2], clearColor_[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glViewport(0, 0, window_.ResolutionWidth(), window_.ResolutionHeight());
        glDrawElements(drawMode_.Mode, drawMode_.NumVertexes, GL_UNSIGNED_INT, nullptr);

        // Release bindings
        glLineWidth(1.0f);
        glUseProgram(0);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void HelloWorldFiddle::UpdateVertexes()
    {
        if (animationEnabled_)
        {
            SetNextVertexPositions();
        }

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId_);

        const unsigned int bufferOffset = 0;
        glBufferSubData(GL_ARRAY_BUFFER,
            bufferOffset,
            triangleModel_->VertexDataByteSize(),
            &triangleModel_->Vertexes[0]);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void HelloWorldFiddle::UpdateVertex(glm::vec4& vertex, glm::vec4& direction) const
    {
        const auto velocity= vertexMoveSpeed_ * direction;

        vertex += static_cast<float>(deltaTime_) * velocity;

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
        const auto nextTime = Timer::Get();
        deltaTime_ = static_cast<float>(nextTime - lastTime_);
        lastTime_ = nextTime;
    }

    void HelloWorldFiddle::SetNextVertexPositions()
    {
        UpdateVertex(triangleModel_->Vertexes[0].Position, vertex1Direction_);
        UpdateVertex(triangleModel_->Vertexes[1].Position, vertex2Direction_);
        UpdateVertex(triangleModel_->Vertexes[2].Position, vertex3Direction_);
    }

    void HelloWorldFiddle::ChangeDrawMode(const DrawMode& nextMode)
    {
        drawMode_ = nextMode;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId_);

        const unsigned int bufferOffset = 0;
        if (nextMode.Mode == GL_LINES)
        {
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
                bufferOffset,
                std::size(lineIndexes_) * sizeof(unsigned int),
                &lineIndexes_[0]);
        }
        else
        {
            glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,
                bufferOffset,
                triangleModel_->IndexDataByteSize(),
                &triangleModel_->Indexes[0]);
        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    glm::vec4 HelloWorldFiddle::GetRandomVertexDirection()
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        const std::uniform_real_distribution<> dist(-1.0f, 1.0f);

        return { dist(rng), dist(rng), 0.0f, 0.0f };
    }

    void HelloWorldFiddle::DrawDescription() const
    {
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::TextWrapped("%s", Description().c_str());
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();
    }

    void HelloWorldFiddle::DrawModeSelector()
    {
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        if (ImGui::BeginCombo("Draw Mode", drawMode_.DisplayName.c_str()))
        {
            for (const auto& mode : drawModes_)
            {
                const auto isSelected = drawMode_.Mode == mode.first;

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
        ImGui::ColorEdit4("glClearColor", &clearColor_[0]);
        ImGui::ColorEdit4("Vertex 1", &triangleModel_->Vertexes[0].Color[0]);
        ImGui::ColorEdit4("Vertex 2", &triangleModel_->Vertexes[1].Color[0]);
        ImGui::ColorEdit4("Vertex 3", &triangleModel_->Vertexes[2].Color[0]);
    }

    void HelloWorldFiddle::DrawPositionControls()
    {
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Position Controls");
        ImGui::Separator();
        if (ImGui::Button("Reset"))
        {
            animationEnabled_ = false;
            triangleModel_->Vertexes[0].Position = { 0.0f,  1.0f, 0.0f, 1.0f };
            triangleModel_->Vertexes[1].Position = { 1.0f, -1.0f, 0.0f, 1.0f };
            triangleModel_->Vertexes[2].Position = { -1.0f, -1.0f, 0.0f, 1.0f };
            vertex1Direction_ = GetRandomVertexDirection();
            vertex2Direction_ = GetRandomVertexDirection();
            vertex3Direction_ = GetRandomVertexDirection();
        }

        /*
        SliderFloat2 takes the address of an array of two floats as the second argument.
        Position is an array of 4 floats, but this works because SliderFloat2 only requires that it can index 2 elements in the array.
        */
        ImGui::SliderFloat2("Vertex 1", &triangleModel_->Vertexes[0].Position[0], -1.0f, 1.0f);
        ImGui::SliderFloat2("Vertex 2", &triangleModel_->Vertexes[1].Position[0], -1.0f, 1.0f);
        ImGui::SliderFloat2("Vertex 3", &triangleModel_->Vertexes[2].Position[0], -1.0f, 1.0f);
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Checkbox("Animation", &animationEnabled_);
        ImGui::SliderFloat("Speed", &vertexMoveSpeed_, 0.0f, 5.0f);
    }

    void HelloWorldFiddle::DrawLineControls()
    {
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Line Controls");
        ImGui::Separator();
        ImGui::SliderFloat("Line Width", &lineWidth_, 1.0f, 10.0f);
    }

    void HelloWorldFiddle::DrawPointControls()
    {
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Point Controls");
        ImGui::Separator();
        ImGui::SliderFloat("Point Size", &pointSize_, 1.0f, 100.0f);
    }

    void HelloWorldFiddle::RenderUi()
    {
        if (!attached_)
            return;

        ImGui::Begin("DemoWidget");

        DrawDescription();
        DrawModeSelector();
        DrawColorControls();
        DrawPositionControls();

        if (drawMode_.Mode == GL_LINES)
        {
            DrawLineControls();
        }
        if (drawMode_.Mode == GL_POINTS)
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
            frameBufferId_ = event.NextRenderTargetId();
        };
    }

    EventHandler<AspectRatioChangeEvent> HelloWorldFiddle::OnAspectRatioChange()
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

    void HelloWorldFiddle::Attach()
    {
        if (attached_) return;

        LogTrace("Attaching HelloWorldFiddle");

        //Layer settings
        glEnable(GL_PROGRAM_POINT_SIZE);
        glLineWidth(lineWidth_);

        //Buffer setup
        glGenVertexArrays(1, &vertexArrayId_);
        glBindVertexArray(vertexArrayId_);
        glGenBuffers(1, &vertexBufferId_);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId_);
        glBufferData(GL_ARRAY_BUFFER, triangleModel_->VertexDataByteSize(), &triangleModel_->Vertexes[0], GL_STATIC_DRAW);

        glGenBuffers(1, &indexBufferId_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId_);

        //Allocate a buffer that can hold the larger of the two index buffers, in this case the line indexes are larger than the triangle indexes.
        const auto indexBufferByteSize = std::size(lineIndexes_) * sizeof(unsigned int);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferByteSize, &triangleModel_->Indexes[0], GL_STATIC_DRAW);

        //Vertex Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, Vertex1::ELEMENTS_PER_POSITION, Vertex1::POSITION_TYPE, GL_FALSE, Vertex1::VERTEX_BYTE_SIZE, reinterpret_cast<void*>(offsetof(Vertex1, Position)));

        //Vertex Color
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, Vertex1::ELEMENTS_PER_COLOR, Vertex1::COLOR_TYPE, GL_FALSE, Vertex1::VERTEX_BYTE_SIZE, reinterpret_cast<void*>(offsetof(Vertex1, Color)));

        //Release Bindings
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);		

        shaderId_ = CreateShader("res/shaders/HelloWorldFiddle_Vertex.shader", "res/shaders/HelloWorldFiddle_Fragment.shader");
        pointSizeUniformLocation_ = glGetUniformLocation(shaderId_, "u_PointSize");
        projMatrixUniformLocation_ = glGetUniformLocation(shaderId_, "u_Proj");

        attached_ = true;
    }

    void HelloWorldFiddle::Detach()
    {
        if (!attached_) return;

        LogTrace("Detaching HelloWorldFiddle");

        glDisable(GL_PROGRAM_POINT_SIZE);
        glLineWidth(1.0f);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDeleteProgram(shaderId_);
        glDeleteBuffers(1, &vertexBufferId_);

        attached_ = false;
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
