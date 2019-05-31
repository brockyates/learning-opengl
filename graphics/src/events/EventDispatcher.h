#pragma once

#include "Event.h"

namespace Graphics {

    class EventDispatcher
    {
    public:
        explicit EventDispatcher(const Event& e)
            : event_(e)
        {}

        template <typename TEventType, typename FEventHandler>
        void Dispatch(FEventHandler eventHandler)
        {
            if (event_.Type() == TEventType::GetStaticType())
            {
                eventHandler(*static_cast<const TEventType*>(&event_));
            }
        }

    private:
        const Event& event_;
    };

}
