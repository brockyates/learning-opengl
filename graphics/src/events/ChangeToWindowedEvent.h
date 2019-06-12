#pragma once

#include "Event.h"

namespace Graphics
{
    class ChangeToWindowedEvent final : public Event
    {
    public:
        ChangeToWindowedEvent();

        [[nodiscard]] EventType Type() const override;
        static EventType GetStaticType();
    };
}
