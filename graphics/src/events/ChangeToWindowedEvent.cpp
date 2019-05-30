#include "pch.h"
#include "ChangeToWindowedEvent.h"

#include "EventType.h"

namespace graphics {

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
