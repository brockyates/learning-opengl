#pragma once

#include "events/Event.h"
#include "events/RenderTargetChangeEvent.h"

#include "layers/Layer.h"

#include "models/Model.h"

#include "renderer/RendererTypes.h"

#include <glm/glm.hpp>

#include <memory>

namespace Graphics
{
    class Window;

    class GlPolygonModeDemo final : public Layer
    {
    public:
        GlPolygonModeDemo(const Window& window, EventHandler<Event> eventCallback);

        void RenderScene() override;
        void RenderUi() override;

        void Attach() override;
        void Detach() override;
        [[nodiscard]] bool IsAttached() const override { return attached_; }

        [[nodiscard]] std::string PopupText() const override;
        [[nodiscard]] std::string Description() const override;

        void OnEvent(const Event& event) override;

    private:
        //Event handlers
        EventHandler<RenderTargetChangeEvent> OnRenderTargetChanged();

        //Scene
        glm::vec4 backgroundColor_ = { 0.5f, 0.5f, 0.5f, 1.0f };
        std::unique_ptr<Model> triangle_;
        bool attached_ = false;

        //OpenGL state
        FrameBuffer frameBuffer_;
        VertexArray vertexArray_;
        VertexBuffer vertexBuffer_;
        IndexBuffer indexBuffer_;
        ShaderProgram shader_;
    };
}
