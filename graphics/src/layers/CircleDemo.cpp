#include "pch.h"
#include "CircleDemo.h"

#include "events/EventDispatcher.h"

#include "imgui/ImGuiHelpers.h"

#include "logging/Log.h"

#include "models/Circle.h"

#include "renderer/Renderer.h"
#include "types/Timer.h"
#include "window/Window.h"

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

        Renderer::SetLineWidth(3.0f);

        // Bindings
        Renderer::BindFrameBuffer(frameBuffer_);
        Renderer::BindVertexArray(vertexArray_);

        // Draw
        Renderer::SetClearColor(backgroundColor_);
        Renderer::ClearColorBuffer();
        Renderer::SetViewPort(0, 0, window_.ResolutionWidth(), window_.ResolutionHeight());
        
        Renderer::UseShader(triangleShader_);
        Renderer::SetUniform(triangleProjMatrixUniform_, projectionMatrix_);
        Renderer::BindIndexBuffer(triangleIndexBuffer_);
        Renderer::DrawTriangleIndexes(circleModel_->NumIndexes());

        Renderer::UseShader(lineShader_);
        Renderer::SetUniform(lineProjMatrixUniform_, projectionMatrix_);
        Renderer::SetUniform(lineColorUniform_, lineColor_);
        Renderer::BindIndexBuffer(lineIndexBuffer_);
        Renderer::DrawLineIndexes(numLineIndexes_);

        // Release bindings
        Renderer::ResetLineWidth();
        Renderer::UnbindAll();
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
            frameBuffer_ = event.NextRenderTarget();
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
        {
            return;
        }

        vertexCount_ = nextVertexes_;
        circleModel_ = std::make_unique<Circle>(vertexCount_);
        const auto bufferOffset = 0u;
        const auto lineIndexes = circleModel_->MakeIndexesForLineDrawMode(vertexCount_);
        const auto lineIndexByteSize = static_cast<uint32_t>(std::size(lineIndexes) * sizeof(unsigned int));
        numLineIndexes_ = static_cast<unsigned int>(std::size(lineIndexes));

        //Update vertex buffer
        Renderer::BindVertexBuffer(vertexBuffer_);
        Renderer::VertexBufferSubData(bufferOffset, circleModel_->VertexDataByteSize(), circleModel_->Vertexes);
        Renderer::UnbindVertexBuffer();

        //Update index buffers
        Renderer::BindIndexBuffer(triangleIndexBuffer_);
        Renderer::IndexBufferSubData(bufferOffset, circleModel_->IndexDataByteSize(), circleModel_->Indexes);
        Renderer::BindIndexBuffer(lineIndexBuffer_);
        Renderer::IndexBufferSubData(bufferOffset, lineIndexByteSize, lineIndexes);
        Renderer::UnbindIndexBuffer();
    }

    void CircleDemo::AnimateSides()
    {
        if (!animationEnabled_)
        {
            return;
        }

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
        Renderer::EnablePointSize();

        //Buffer setup
        vertexArray_ = Renderer::GenVertexArray();
        Renderer::BindVertexArray(vertexArray_);
        vertexBuffer_ = Renderer::GenVertexBuffer();
        Renderer::BindVertexBuffer(vertexBuffer_);
        Renderer::SetVertexesForStaticDraw(circleModel_->VertexDataByteSize(), circleModel_->Vertexes);

        triangleIndexBuffer_ = Renderer::GenIndexBuffer();
        Renderer::BindIndexBuffer(triangleIndexBuffer_);
        Renderer::SetIndexesForStaticDraw(circleModel_->IndexDataByteSize(), circleModel_->Indexes);

        const auto lineIndexes = circleModel_->MakeIndexesForLineDrawMode(vertexCount_);
        const auto lineIndexByteSize = static_cast<uint32_t>(std::size(lineIndexes) * sizeof(unsigned int));
        numLineIndexes_ = static_cast<unsigned int>(std::size(lineIndexes));
        lineIndexBuffer_ = Renderer::GenIndexBuffer();
        Renderer::BindIndexBuffer(lineIndexBuffer_);
        Renderer::SetIndexesForStaticDraw(lineIndexByteSize, lineIndexes);

        Renderer::SetVertexAttrib0(Vertex1::ELEMENTS_PER_POSITION, Vertex1::POSITION_TYPE, false, Vertex1::VERTEX_BYTE_SIZE, offsetof(Vertex1, Position)); //Vertex Position
        Renderer::SetVertexAttrib1(Vertex1::ELEMENTS_PER_COLOR, Vertex1::COLOR_TYPE, false, Vertex1::VERTEX_BYTE_SIZE, offsetof(Vertex1, Color));          //Vertex Color

        //Release bindings
        Renderer::UnbindVertexArray();
        Renderer::UnbindVertexBuffer();
        Renderer::UnbindIndexBuffer();

        triangleShader_ = Renderer::CreateShaderProgram("res/shaders/CircleDemo_TriangleVertex.shader", "res/shaders/CircleDemo_TriangleFragment.shader");
        triangleProjMatrixUniform_ = Renderer::GetUniform(triangleShader_, "u_Proj");

        lineShader_ = Renderer::CreateShaderProgram("res/shaders/CircleDemo_LineVertex.shader", "res/shaders/CircleDemo_LineFragment.shader");
        lineColorUniform_ = Renderer::GetUniform(lineShader_, "u_LineColor");
        lineProjMatrixUniform_ = Renderer::GetUniform(lineShader_, "u_Proj");

        attached_ = true;
    }

    void CircleDemo::Detach()
    {
        if (!attached_) return;

        LogTrace("Detaching CircleDemo");

        Renderer::DisablePointSize();

        Renderer::UnbindAll();

        Renderer::DeleteShader(triangleShader_);
        Renderer::DeleteShader(lineShader_);
        Renderer::DeleteIndexBuffer(triangleIndexBuffer_);
        Renderer::DeleteIndexBuffer(lineIndexBuffer_);
        Renderer::DeleteVertexBuffer(vertexBuffer_);

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
