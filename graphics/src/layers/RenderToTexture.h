#pragma once

#include "layers/Layer.h"
#include "ShaderHelpers.h"

#include "events/ChangeToWindowedEvent.h"
#include "events/ChangeResolutionEvent.h"
#include "events/Event.h"
#include "Window.h"

#include <glm/glm.hpp>

namespace Graphics {

    struct WindowProperties;

    class RenderToTexture : public Layer
    {
    public:
        RenderToTexture(Window* window, EventHandler<Event> eventCallback);

        virtual void RenderScene() override;
        virtual void RenderUI() override;

        virtual void Attach() override;
        virtual void Detach() override;
        virtual bool IsAttached() override { return m_Attached; }

        virtual std::string GetPopupText() const override;
        virtual std::string GetDescription() const override;

        virtual void OnEvent(const Event& event) override;

    private:
        //Event handlers
        EventHandler<ChangeResolutionEvent> OnResolutionChange();
        EventHandler<ChangeToWindowedEvent> OnChangeToWindowed();

    private:
        unsigned int m_ShaderID = 0;
        unsigned int m_VertexArrayID = 0;
        unsigned int m_VertexBufferID = 0;
        bool m_Attached = false;

        glm::vec4 m_ClearColor = { 0.5f, 0.5f, 0.5f, 1.0f };

        std::vector<float> m_Vertexes =
        {
             0.0f,  1.0f,
             1.0f, -1.0f,
            -1.0f, -1.0f,
        };

    private:
        unsigned int m_FrameBufferID = 0;
        unsigned int m_RenderedTextureID = 0;
        unsigned int m_RenderBufferID = 0;
    };

}
