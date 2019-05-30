#pragma once

#include "Event.h"

namespace Graphics {

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent();

        virtual EventType Type() const override;
        static EventType GetStaticType();
    };

}
