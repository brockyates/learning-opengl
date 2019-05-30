#pragma once

#include "Event.h"

namespace Graphics {

    class ChangeToFullscreenEvent : public Event
    {
    public:
        ChangeToFullscreenEvent();

        virtual EventType Type() const override;
        static EventType GetStaticType();
    };

}
