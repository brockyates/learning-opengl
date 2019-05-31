#pragma once

#include "events/Event.h"
#include "events/ChangeToFullscreenEvent.h"
#include "events/ChangeToWindowedEvent.h"
#include "events/ResolutionChangeEvent.h"

#include "layers/Layer.h"

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

    private:
        //Event handlers
        EventHandler<ChangeToFullscreenEvent> OnChangeToFullscreen();
        EventHandler<ChangeToWindowedEvent> OnChangeToWindowed();
        EventHandler<ResolutionChangeEvent> OnResolutionChange();

    private:
        //OpenGL state
        unsigned int windowedRenderTargetId_ = 0;
        unsigned int fullscreenRenderTargetId_ = 0;

        unsigned int renderedTextureId_ = 0;
        unsigned int renderBufferId_ = 0;

        float aspectRatio_ = 0.0f;
    };

}
