#pragma once

#include "Event.h"

namespace Graphics {

    class ChangeToWindowedEvent : public Event
    {
    public:
        ChangeToWindowedEvent();

        virtual EventType Type() const override;
        static EventType GetStaticType();
    };

}
