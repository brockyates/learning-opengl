#include "pch.h"
#include "WindowCloseEvent.h"

#include "EventType.h"

namespace graphics {

    WindowCloseEvent::WindowCloseEvent()
    {}

    EventType WindowCloseEvent::Type() const
    {
        return GetStaticType();
    }

    EventType WindowCloseEvent::GetStaticType()
    {
        return EventType::WindowCloseEvent;
    }
};
