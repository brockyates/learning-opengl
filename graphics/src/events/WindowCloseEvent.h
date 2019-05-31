#pragma once

#include "Event.h"

namespace Graphics {

    class WindowCloseEvent final : public Event
    {
    public:
        WindowCloseEvent();

        [[nodiscard]] virtual EventType Type() const override;
        static EventType GetStaticType();
    };

}
