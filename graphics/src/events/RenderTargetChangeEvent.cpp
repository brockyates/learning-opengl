#include "pch.h"
#include "RenderTargetChangeEvent.h"

#include "EventType.h"

namespace Graphics {

    RenderTargetChangeEvent::RenderTargetChangeEvent(const FrameBuffer nextRenderTarget)
        : nextRenderTarget_(nextRenderTarget)
    {}

    EventType RenderTargetChangeEvent::Type() const
    {
        return GetStaticType();
    }

    EventType RenderTargetChangeEvent::GetStaticType()
    {
        return EventType::RenderTargetEvent;
    }

    FrameBuffer RenderTargetChangeEvent::NextRenderTarget() const
    {
        return nextRenderTarget_;
    }

}
