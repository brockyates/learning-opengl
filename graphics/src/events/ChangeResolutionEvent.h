#pragma once

#include "Event.h"

namespace Graphics {

    class ChangeResolutionEvent : public Event
    {
    public:
        virtual EventType Type() const override { return GetStaticType(); }

        static EventType GetStaticType()
        {
            return EventType::ChangeResolutionEvent;
        }
    };

}
