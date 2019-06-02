#pragma once

#include "events/Event.h"
#include "events/RenderTargetChangeEvent.h"

#include "layers/Layer.h"

namespace Graphics {

    class Window;

    class HelloWorld final : public Layer
    {
    public:
        HelloWorld(const Window& window, EventHandler<Event> eventCallback);

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

        //OpenGL state
        unsigned int frameBufferId_ = 0;
        unsigned int shaderId_ = 0;
        unsigned int vertexArrayId_ = 0;
        unsigned int vertexBufferId_ = 0;

        std::vector<float> vertexes_ =
        {
             0.0f,  1.0f,
             1.0f, -1.0f,
            -1.0f, -1.0f,
        };

        bool attached_ = false;
    };

}
