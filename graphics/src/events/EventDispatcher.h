#pragma once

#include "Event.h"

namespace Graphics {

    class EventDispatcher
    {
    public:
        EventDispatcher(Event& e)
            : m_Event(e)
        {}

        template <typename TEventType, typename FEventHandler>
        void Dispatch(FEventHandler eventHandler)
        {
            if (m_Event.GetType() == TEventType::GetStaticType())
            {
                eventHandler(*static_cast<TEventType*>(&m_Event));
            }
        }

    private:
        Event& m_Event;
    };

}
