#pragma once

#include "Event.h"

namespace graphics {

    class EventDispatcher
    {
    public:
        EventDispatcher(const Event& e)
            : m_Event(e)
        {}

        template <typename TEventType, typename FEventHandler>
        void Dispatch(FEventHandler eventHandler)
        {
            if (m_Event.Type() == TEventType::GetStaticType())
            {
                eventHandler(*static_cast<const TEventType*>(&m_Event));
            }
        }

    private:
        const Event& m_Event;
    };

}
