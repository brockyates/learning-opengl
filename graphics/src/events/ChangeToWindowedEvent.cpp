#include "pch.h"
#include "ChangeToWindowedEvent.h"

#include "EventType.h"

namespace Graphics {

    ChangeToWindowedEvent::ChangeToWindowedEvent()
    {}

    EventType ChangeToWindowedEvent::Type() const
    {
        return GetStaticType();
    }

    EventType ChangeToWindowedEvent::GetStaticType()
    {
        return EventType::ChangeToWindowedEvent;
    }
};
