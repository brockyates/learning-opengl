#include "pch.h"
#include "ChangeToFullscreenEvent.h"

#include "EventType.h"

namespace Graphics
{
    EventType ChangeToFullscreenEvent::Type() const
    {
        return GetStaticType();
    }

    EventType ChangeToFullscreenEvent::GetStaticType()
    {
        return EventType::ChangeToFullscreenEvent;
    }
}
