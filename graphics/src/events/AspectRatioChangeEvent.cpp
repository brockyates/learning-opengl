#include "pch.h"
#include "AspectRatioChangeEvent.h"

#include "EventType.h"

namespace Graphics {

    AspectRatioChangeEvent::AspectRatioChangeEvent(const float aspectRatio)
        : aspectRatio_(aspectRatio)
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
        return aspectRatio_;
    }

}
