#pragma once

#include "events/Event.h"
#include "events/AspectRatioChangeEvent.h"
#include "events/RenderTargetChangeEvent.h"

#include "layers/Layer.h"

#include "models/Model.h"

#include "renderer/RendererTypes.h"

#include <glm/glm.hpp>

#include <memory>

namespace Graphics
{
    struct WindowProperties;
    class Window;

    class HelloWorldFiddle final : public Layer
    {
    public:
        HelloWorldFiddle(const Window& window, EventHandler<Event> eventCallback);

        void RenderScene() override;
        void RenderUi() override;

        void Attach() override;
        void Detach() override;
        [[nodiscard]] bool IsAttached() const override { return attached_; }

        [[nodiscard]] std::string PopupText() const override;
        [[nodiscard]] std::string Description() const override;

        void OnEvent(const Event& event) override;

    private:
        //This struct is only meaningful in the context of this demo, I don't want it to exist outside of HelloWorldFiddle.
        struct DrawMode
        {
            int32_t Mode{};
            uint32_t NumVertexes{};
            std::string DisplayName;
        };

        //Event handlers
        EventHandler<RenderTargetChangeEvent> OnRenderTargetChanged();
        EventHandler<AspectRatioChangeEvent> OnAspectRatioChange();

        //Scene
        void UpdateVertexes();
        void UpdateVertex(glm::vec4& vertex, glm::vec4& direction) const;
        void UpdateTiming();
        void SetNextVertexPositions();
        void ChangeDrawMode(const DrawMode& nextMode);
        [[nodiscard]] static glm::vec4 GetRandomVertexDirection();

        bool attached_ = false;
        double lastTime_;
        double deltaTime_ = 0;
        glm::vec4 backgroundColor_ = { 0.15f, 0.15f, 0.15f, 1.0f };
        float lineWidth_ = 5.0f;
        float pointSize_ = 30.0f;
        std::unordered_map<int32_t, DrawMode> drawModes_;
        DrawMode drawMode_;
        glm::mat4 projectionMatrix_;

        //UI
        void DrawDescription() const;
        void DrawModeSelector();
        void DrawColorControls();
        void DrawPositionControls();
        void DrawLineControls();
        void DrawPointControls();

        //Buffer data
        std::unique_ptr<Model> triangle_;
        std::vector<uint32_t> lineIndexes_ = { 0, 1, 1, 2, 2, 0 };

        //Animation parameters
        bool animationEnabled_ = false;
        float vertexMoveSpeed_ = 0.5f;

        glm::vec4 vertex1Direction_ = GetRandomVertexDirection();
        glm::vec4 vertex2Direction_ = GetRandomVertexDirection();
        glm::vec4 vertex3Direction_ = GetRandomVertexDirection();

        //OpenGL state
        FrameBuffer frameBuffer_;
        VertexArray vertexArray_;
        VertexBuffer vertexBuffer_;
        IndexBuffer indexBuffer_;
        ShaderProgram shader_;
        Uniform projMatrixUniform_;
        Uniform pointSizeUniform_;
    };
}
