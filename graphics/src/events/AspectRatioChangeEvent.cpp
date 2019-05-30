#include "pch.h"
#include "AspectRatioChangeEvent.h"

#include "EventType.h"

namespace graphics {

    AspectRatioChangeEvent::AspectRatioChangeEvent(float aspectRatio)
        : m_AspectRatio(aspectRatio)
    {}

    EventType AspectRatioChangeEvent::Type() const
    {
        return GetStaticType();
    }

    EventType AspectRatioChangeEvent::GetStaticType()
    {
        return EventType::AspectRatioChange;
    }

    float AspectRatioChangeEvent::NewAspectRatio() const
    {
        return m_AspectRatio;
    }

}
