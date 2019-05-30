#pragma once

#include "events/Event.h"
#include "events/ChangeToFullscreenEvent.h"
#include "events/RenderTargetChangeEvent.h"

#include "layers/Layer.h"

namespace Graphics {

    class Window;

    class HelloWorld : public Layer
    {
    public:
        HelloWorld(const Window& window, EventHandler<Event> eventCallback);

        virtual void RenderScene() override;
        virtual void RenderUI() override;

        virtual void Attach() override;
        virtual void Detach() override;
        [[nodiscard]] virtual bool IsAttached() const override { return m_Attached; }

        [[nodiscard]] virtual std::string PopupText() const override;
        [[nodiscard]] virtual std::string Description() const override;

        virtual void OnEvent(const Event& event) override;

    private:
        //Event handlers
        EventHandler<RenderTargetChangeEvent> OnRenderTargetChanged();

    private:
        //OpenGL state
        unsigned int m_FrameBufferID = 0;
        unsigned int m_ShaderID = 0;
        unsigned int m_VertexArrayID = 0;
        unsigned int m_VertexBufferID = 0;

        std::vector<float> m_Vertexes =
        {
             0.0f,  1.0f,
             1.0f, -1.0f,
            -1.0f, -1.0f,
        };

    private:
        bool m_Attached = false;
    };

}
