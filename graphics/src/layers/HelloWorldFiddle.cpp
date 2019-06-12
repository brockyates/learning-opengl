#include "pch.h"
#include "HelloWorldFiddle.h"

#include "events/EventDispatcher.h"

#include "logging/Log.h"

#include "models/ModelGenerator.h"
#include "renderer/Renderer.h"
#include "types/Timer.h"
#include "window/Window.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

#include <random>
#include <utility>

namespace Graphics
{
    HelloWorldFiddle::HelloWorldFiddle(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, std::move(eventCallback), "Hello World Fiddle")
        , lastTime_(Timer::Get())
        , drawModes_({
            { GL_TRIANGLES, {GL_TRIANGLES, 3, "Triangles" }},
            { GL_LINES,     {GL_LINES,     6, "Lines"     }},
            { GL_POINTS,    {GL_POINTS,    3, "Points"    }}
        })
        , drawMode_(drawModes_[GL_TRIANGLES])
        , projectionMatrix_(glm::ortho(-1.0f * window_.AspectRatio(), 1.0f * window_.AspectRatio(), -1.0f, 1.0f))
        , triangle_(ModelGenerator::MakeTriangle())
    {}

    void HelloWorldFiddle::RenderScene()
    {
        if (!attached_)
            return;

        UpdateTiming();
        UpdateVertexes();

        Renderer::SetLineWidth(lineWidth_);

        //Bindings
        Renderer::BindFrameBuffer(frameBuffer_);
        Renderer::BindVertexArray(vertexArray_);
        Renderer::UseShader(shader_);
        Renderer::SetUniform(pointSizeUniform_, pointSize_);
        Renderer::SetUniform(projMatrixUniform_, projectionMatrix_);

        //Draw
        Renderer::SetClearColor(backgroundColor_);
        Renderer::ClearColorBuffer();
        Renderer::SetViewPort(0, 0, window_.ResolutionWidth(), window_.ResolutionHeight());
        Renderer::DrawIndexes(drawMode_.Mode, drawMode_.NumVertexes);

        //Cleanup
        Renderer::ResetLineWidth();
        Renderer::UnbindAll();
    }

    void HelloWorldFiddle::UpdateVertexes()
    {
        if (animationEnabled_)
        {
            SetNextVertexPositions();
        }

        const auto bufferOffset = 0u;
        Renderer::BindVertexBuffer(vertexBuffer_);
        Renderer::VertexBufferSubData(bufferOffset, triangle_->VertexDataByteSize(), triangle_->Vertexes);
        Renderer::UnbindVertexBuffer();
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
        UpdateVertex(triangle_->Vertexes[0].Position, vertex1Direction_);
        UpdateVertex(triangle_->Vertexes[1].Position, vertex2Direction_);
        UpdateVertex(triangle_->Vertexes[2].Position, vertex3Direction_);
    }

    void HelloWorldFiddle::ChangeDrawMode(const DrawMode& nextMode)
    {
        drawMode_ = nextMode;

        Renderer::BindIndexBuffer(indexBuffer_);

        const auto bufferOffset = 0u;
        if (nextMode.Mode == GL_LINES)
        {
            Renderer::IndexBufferSubData(bufferOffset, static_cast<uint32_t>(std::size(lineIndexes_) * sizeof(uint32_t)),lineIndexes_);
        }
        else
        {
            Renderer::IndexBufferSubData(bufferOffset, triangle_->IndexDataByteSize(), triangle_->Indexes);
        }

        Renderer::UnbindIndexBuffer();
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
        ImGui::ColorEdit4("glClearColor", &backgroundColor_[0]);
        ImGui::ColorEdit4("Vertex 1", &triangle_->Vertexes[0].Color[0]);
        ImGui::ColorEdit4("Vertex 2", &triangle_->Vertexes[1].Color[0]);
        ImGui::ColorEdit4("Vertex 3", &triangle_->Vertexes[2].Color[0]);
    }

    void HelloWorldFiddle::DrawPositionControls()
    {
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Text("Position Controls");
        ImGui::Separator();
        if (ImGui::Button("Reset"))
        {
            animationEnabled_ = false;
            triangle_->Vertexes[0].Position = { 0.0f,  1.0f, 0.0f, 1.0f };
            triangle_->Vertexes[1].Position = { 1.0f, -1.0f, 0.0f, 1.0f };
            triangle_->Vertexes[2].Position = { -1.0f, -1.0f, 0.0f, 1.0f };
            vertex1Direction_ = GetRandomVertexDirection();
            vertex2Direction_ = GetRandomVertexDirection();
            vertex3Direction_ = GetRandomVertexDirection();
        }

        /*
        SliderFloat2 takes the address of an array of two floats as the second argument.
        Position is an array of 4 floats, but this works because SliderFloat2 only requires that it can index 2 elements in the array.
        */
        ImGui::SliderFloat2("Vertex 1", &triangle_->Vertexes[0].Position[0], -1.0f, 1.0f);
        ImGui::SliderFloat2("Vertex 2", &triangle_->Vertexes[1].Position[0], -1.0f, 1.0f);
        ImGui::SliderFloat2("Vertex 3", &triangle_->Vertexes[2].Position[0], -1.0f, 1.0f);
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
            frameBuffer_ = event.NextRenderTarget();
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
        Renderer::EnablePointSize();
        Renderer::SetLineWidth(lineWidth_);

        //Buffer setup
        vertexArray_ = Renderer::GenVertexArray();
        Renderer::BindVertexArray(vertexArray_);

        vertexBuffer_ = Renderer::GenVertexBuffer();
        Renderer::BindVertexBuffer(vertexBuffer_);
        Renderer::SetVertexesForStaticDraw(triangle_->VertexDataByteSize(), triangle_->Vertexes);

        indexBuffer_ = Renderer::GenIndexBuffer();
        Renderer::BindIndexBuffer(indexBuffer_);

        //Allocate a buffer that can hold the larger of the two index buffers, in this case the line indexes are larger than the triangle indexes.
        const auto indexBufferByteSize = static_cast<uint32_t>(std::size(lineIndexes_) * sizeof(uint32_t));
        Renderer::SetIndexesForStaticDraw(indexBufferByteSize, triangle_->Indexes);

        //Vertex Position
        Renderer::SetVertexAttrib0(Vertex1::ELEMENTS_PER_POSITION, Vertex1::POSITION_TYPE, false, Vertex1::VERTEX_BYTE_SIZE, offsetof(Vertex1, Position));

        //Vertex Color
        Renderer::SetVertexAttrib1(Vertex1::ELEMENTS_PER_COLOR, Vertex1::COLOR_TYPE, false, Vertex1::VERTEX_BYTE_SIZE, offsetof(Vertex1, Color));

        shader_ = Renderer::CreateShaderProgram("res/shaders/HelloWorldFiddle_Vertex.shader", "res/shaders/HelloWorldFiddle_Fragment.shader");
        pointSizeUniform_ = Renderer::GetUniform(shader_, "u_PointSize");
        projMatrixUniform_ = Renderer ::GetUniform(shader_, "u_Proj");

        attached_ = true;
        Renderer::UnbindAll();
    }

    void HelloWorldFiddle::Detach()
    {
        if (!attached_) return;

        LogTrace("Detaching HelloWorldFiddle");

        Renderer::DisablePointSize();
        Renderer::ResetLineWidth();

        Renderer::UnbindAll();

        Renderer::DeleteShader(shader_);
        Renderer::DeleteVertexBuffer(vertexBuffer_);
        Renderer::DeleteIndexBuffer(indexBuffer_);

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
