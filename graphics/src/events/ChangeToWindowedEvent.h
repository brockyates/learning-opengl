#pragma once

#include "Event.h"

namespace graphics {

    class ChangeToWindowedEvent : public Event
    {
    public:
        ChangeToWindowedEvent();

        virtual EventType Type() const override;
        static EventType GetStaticType();
    };

}
