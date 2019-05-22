#pragma once

#include "events/EventSystem.h"
#include "layers/Layer.h"
#include "Window.h"

namespace Graphics {

    struct WindowProperties;

    class RenderTargetLayer : public Layer
    {
    public:
        RenderTargetLayer(const Window& window, EventHandler<Event> eventCallback);
        virtual ~RenderTargetLayer() override;

        virtual void RenderUI() override;

        virtual void OnEvent(const Event& event) override;

    private:
        virtual bool IsAttached() const override { return true; }
        virtual void Attach() override;
        virtual void Detach() override;

    private:
        //Event handlers
        EventHandler<ChangeToFullscreenEvent> OnChangeToFullscreen();
        EventHandler<ChangeToWindowedEvent> OnChangeToWindowed();
        EventHandler<ChangeResolutionEvent> OnResolutionChange();

    private:
        //OpenGL state
        unsigned int m_WindowedRenderTargetID = 0;
        unsigned int m_FullscreenRenderTargetID = 0;

        unsigned int m_RenderedTextureID = 0;
        unsigned int m_RenderBufferID = 0;
    };

}