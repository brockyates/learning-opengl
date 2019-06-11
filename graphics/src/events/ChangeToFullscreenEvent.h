#pragma once

#include "Event.h"

namespace Graphics
{
    class ChangeToFullscreenEvent final : public Event
    {
    public:
        ChangeToFullscreenEvent() = default;

        [[nodiscard]] EventType Type() const override;
        static EventType GetStaticType();
    };
}
