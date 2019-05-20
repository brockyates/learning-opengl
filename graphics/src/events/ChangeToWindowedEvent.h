#pragma once

#include "Event.h"

namespace Graphics {

    class ChangeToWindowedEvent : public Event
    {
    public:
        ChangeToWindowedEvent()
        {}

        virtual EventType Type() const override { return GetStaticType(); }

        static EventType GetStaticType()
        {
            return EventType::ChangeToWindowedEvent;
        }
    };

}
