#pragma once

#include "Event.h"

#include "renderer/RendererTypes.h"

namespace Graphics
{
    class RenderTargetChangeEvent final : public Event
    {
    public:
        explicit RenderTargetChangeEvent(FrameBuffer nextRenderTarget);

        [[nodiscard]] EventType Type() const override;
        static EventType GetStaticType();

        [[nodiscard]] FrameBuffer NextRenderTarget() const;

    private:
        FrameBuffer nextRenderTarget_;
    };
}
