#include "pch.h"
#include "BlendDemo.h"

#include "events/EventDispatcher.h"

#include "logging/Log.h"

#include "models/ModelGenerator.h"
#include "renderer/Renderer.h"
#include "window/Window.h"

#include <imgui.h>
#include <utility>

namespace Graphics
{
    BlendDemo::BlendDemo(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, std::move(eventCallback), "Blend Demo")
        , triangle_(ModelGenerator::MakeTriangle())
    {}

    void BlendDemo::RenderScene()
    {
        if (!attached_)
            return;

        // Bindings
        Renderer::BindFrameBuffer(frameBuffer_);
        Renderer::BindVertexArray(vertexArray_);
        Renderer::UseShader(shader_);

        // Draw
        Renderer::SetClearColor(backgroundColor_);
        Renderer::ClearColorBuffer();

        Renderer::SetViewPort(0, 0, window_.ResolutionWidth(), window_.ResolutionHeight());
        Renderer::DrawTriangleIndexes(triangle_->IndexCount());

        // Release bindings
        Renderer::UnbindAll();
    }

    void BlendDemo::RenderUi()
    {
        if (!attached_)
            return;

        ImGui::Begin("DemoWidget");

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::TextWrapped("%s", Description().c_str());
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();

        ImGui::End();
    }

    void BlendDemo::OnEvent(const Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<RenderTargetChangeEvent>(OnRenderTargetChanged());
    }

    EventHandler<RenderTargetChangeEvent> BlendDemo::OnRenderTargetChanged()
    {
        return [this](const RenderTargetChangeEvent& event)
        {
            frameBuffer_ = event.NextRenderTarget();
        };
    }

    void BlendDemo::Attach()
    {
        if (attached_) return;

        LogTrace("Attaching BlendDemo");

        vertexArray_ = Renderer::GenVertexArray();
        Renderer::BindVertexArray(vertexArray_);

        vertexBuffer_ = Renderer::GenVertexBuffer();
        Renderer::BindVertexBuffer(vertexBuffer_);
        Renderer::SetVertexesForStaticDraw(triangle_->VertexDataByteSize(), triangle_->Vertexes);

        indexBuffer_ = Renderer::GenIndexBuffer();
        Renderer::BindIndexBuffer(indexBuffer_);
        Renderer::SetIndexesForStaticDraw(triangle_->IndexDataByteSize(), triangle_->Indexes);

        Renderer::SetVertexAttrib0(Vertex1::ELEMENTS_PER_POSITION, Vertex1::POSITION_TYPE, false, Vertex1::VERTEX_BYTE_SIZE, offsetof(Vertex1, Position)); //Vertex Position

        shader_ = Renderer::CreateShaderProgram("res/shaders/Minimal_Vertex.shader", "res/shaders/Minimal_Fragment.shader");
        attached_ = true;

        Renderer::UnbindAll();
    }

    void BlendDemo::Detach()
    {
        if (!attached_) return;

        LogTrace("Detaching BlendDemo");

        Renderer::UnbindAll();

        Renderer::DeleteShader(shader_);
        Renderer::DeleteVertexBuffer(vertexBuffer_);
        Renderer::DeleteIndexBuffer(indexBuffer_);

        attached_ = false;
    }

    std::string BlendDemo::PopupText() const
    {
        return "Basic demo of blending.";
    }

    std::string BlendDemo::Description() const
    {
        return "This is a basic demonstration of blending in OpenGL.";
    }
}
