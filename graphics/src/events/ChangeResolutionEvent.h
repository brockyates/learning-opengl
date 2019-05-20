#pragma once

#include "Event.h"
#include "ResolutionSetting.h"

namespace Graphics {

    class ChangeResolutionEvent : public Event
    {
    public:
        ChangeResolutionEvent(ResolutionSetting resolution)
            : m_Resolution(resolution)
        {}

        virtual EventType Type() const override { return GetStaticType(); }

        static EventType GetStaticType()
        {
            return EventType::ChangeResolutionEvent;
        }

        ResolutionSetting ChangeResolutionEvent::NewResolution() const { return m_Resolution; }

    private:
        ResolutionSetting m_Resolution;
    };

}
