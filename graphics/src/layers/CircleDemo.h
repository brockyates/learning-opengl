#pragma once

#include "events/Event.h"
#include "events/RenderTargetChangeEvent.h"
#include "events/AspectRatioChangeEvent.h"

#include "models/Circle.h"

#include "layers/Layer.h"

#include "renderer/RendererTypes.h"

#include <glm/glm.hpp>

namespace Graphics {

    struct Circle;
    class Window;

    class CircleDemo final : public Layer
    {
    public:
        CircleDemo(const Window& window, EventHandler<Event> eventCallback);

        void RenderScene() override;
        void RenderUi() override;
        void OnEvent(const Event& event) override;
        void Attach() override;
        void Detach() override;
        [[nodiscard]] bool IsAttached() const override { return attached_; }
        [[nodiscard]] std::string PopupText() const override;
        [[nodiscard]] std::string Description() const override;

    private:
        //Event handlers
        EventHandler<RenderTargetChangeEvent> OnRenderTargetChange();
        EventHandler<AspectRatioChangeEvent> OnAspectRatioChange();

        //Scene rendering
        void UpdateTiming();
        void UpdateSides();
        void AnimateSides();

        constexpr static int MAX_VERTEXES = 50;
        int vertexCount_ = MAX_VERTEXES;
        int nextVertexes_ = MAX_VERTEXES;
        unsigned int numLineIndexes_ = 0;
        double timeSinceLastChange_ = 0.0;
        float animationInterval_ = 0.5;
        bool sidesIncreasing_ = false;
        bool animationEnabled_ = false;

        std::unique_ptr<Circle> circleModel_;
        glm::mat4 projectionMatrix_;

        //Layer state
        bool attached_ = false;
        double lastTime_;
        double deltaTime_ = 0.0;

        //OpenGL state
        unsigned int frameBufferId_ = 0;
        ShaderProgram triangleShader_ = ShaderProgram{0};
        ShaderProgram lineShader_ = ShaderProgram{ 0 };
        unsigned int vertexArrayId_ = 0;
        unsigned int vertexBufferId_ = 0;
        unsigned int triangleIndexBufferId_ = 0;
        unsigned int lineIndexBufferId_ = 0;
        unsigned int triangleProjMatrixUniformLocation_ = 0;
        unsigned int lineProjMatrixUniformLocation_ = 0;
        unsigned int lineColorUniformLocation_ = 0;
    };

}
