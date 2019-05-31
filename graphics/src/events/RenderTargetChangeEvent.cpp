#include "pch.h"
#include "RenderTargetChangeEvent.h"

#include "EventType.h"

namespace Graphics {

    RenderTargetChangeEvent::RenderTargetChangeEvent(unsigned int nextRenderTargetId)
        : nextRenderTargetId_(nextRenderTargetId)
    {}

    EventType RenderTargetChangeEvent::Type() const
    {
        return GetStaticType();
    }

    EventType RenderTargetChangeEvent::GetStaticType()
    {
        return EventType::RenderTargetChanged;
    }

    unsigned int RenderTargetChangeEvent::NextRenderTargetId() const
    {
        return nextRenderTargetId_;
    }

}
