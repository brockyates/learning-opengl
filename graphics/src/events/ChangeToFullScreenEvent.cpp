#include "pch.h"
#include "ChangeToFullscreenEvent.h"

#include "EventType.h"

namespace graphics {

    ChangeToFullscreenEvent::ChangeToFullscreenEvent()
    {}

    EventType ChangeToFullscreenEvent::Type() const
    {
        return GetStaticType();
    }

    EventType ChangeToFullscreenEvent::GetStaticType()
    {
        return EventType::ChangeToFullscreenEvent;
    }

}
