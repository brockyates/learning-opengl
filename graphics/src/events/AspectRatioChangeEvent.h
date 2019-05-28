#pragma once

#include "Event.h"

namespace Graphics {

    class AspectRatioChangeEvent : public Event
    {
    public:
        AspectRatioChangeEvent(float aspectRatio)
            : m_AspectRatio(aspectRatio)
        {}

        virtual EventType Type() const override { return GetStaticType(); }

        static EventType GetStaticType()
        {
            return EventType::AspectRatioChange;
        }

        float AspectRatioChangeEvent::NewAspectRatio() const { return m_AspectRatio; }

    private:
        float m_AspectRatio;
    };

}
