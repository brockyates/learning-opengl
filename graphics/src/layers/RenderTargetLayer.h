#pragma once

#include "events/Event.h"
#include "events/ChangeToFullscreenEvent.h"
#include "events/ChangeToWindowedEvent.h"
#include "events/ResolutionChangeEvent.h"

#include "layers/Layer.h"

#include "renderer/RendererTypes.h"

namespace Graphics {

    class Window;

    class RenderTargetLayer final : public Layer
    {
    public:
        RenderTargetLayer(const Window& window, EventHandler<Event> eventCallback);
        ~RenderTargetLayer() override;

        RenderTargetLayer(const RenderTargetLayer&) = delete;
        RenderTargetLayer(RenderTargetLayer&&) = delete;

        RenderTargetLayer& operator=(const RenderTargetLayer&) = delete;
        RenderTargetLayer& operator=(RenderTargetLayer&&) = delete;

        void RenderUi() override;
        void OnEvent(const Event& event) override;

    private:
        [[nodiscard]] bool IsAttached() const override { return true; }
        void Attach() override;
        void Detach() override;

        void HandleAspectRatioChange();

        //Event handlers
        EventHandler<ChangeToFullscreenEvent> OnChangeToFullscreen();
        EventHandler<ChangeToWindowedEvent> OnChangeToWindowed();
        EventHandler<ResolutionChangeEvent> OnResolutionChange();

        float aspectRatio_ = 0.0f;

        //OpenGL state
        FrameBuffer windowedRenderTarget_;
        FrameBuffer fullscreenRenderTarget_ = FrameBuffer{ 0 };

        Texture2d renderedTexture_;
        RenderBuffer renderBuffer_;
    };

}
