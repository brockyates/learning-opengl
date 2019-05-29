#pragma once

#include "Event.h"
#include "ResolutionSetting.h"

namespace Graphics {

    class ResolutionChangeEvent : public Event
    {
    public:
        ResolutionChangeEvent(ResolutionSetting resolution)
            : m_Resolution(resolution)
        {}

        virtual EventType Type() const override { return GetStaticType(); }

        static EventType GetStaticType()
        {
            return EventType::ResolutionChangeEvent;
        }

        ResolutionSetting ResolutionChangeEvent::NewResolution() const { return m_Resolution; }

    private:
        ResolutionSetting m_Resolution;
    };

}
