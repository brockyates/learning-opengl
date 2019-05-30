#include "pch.h"
#include "RenderTargetChangeEvent.h"

#include "EventType.h"

namespace Graphics {

    RenderTargetChangeEvent::RenderTargetChangeEvent(unsigned int nextRenderTargetID)
        : m_NextRenderTargetID(nextRenderTargetID)
    {}

    EventType RenderTargetChangeEvent::Type() const
    {
        return GetStaticType();
    }

    EventType RenderTargetChangeEvent::GetStaticType()
    {
        return EventType::RenderTargetChanged;
    }

    unsigned int RenderTargetChangeEvent::NextRenderTargetID() const
    {
        return m_NextRenderTargetID;
    }

}
