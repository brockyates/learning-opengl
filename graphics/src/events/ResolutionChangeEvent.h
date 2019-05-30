#pragma once

#include "Event.h"
#include "ResolutionSetting.h"

namespace graphics {

    class ResolutionChangeEvent : public Event
    {
    public:
        ResolutionChangeEvent(ResolutionSetting resolution);

        virtual EventType Type() const override;
        static EventType GetStaticType();

        ResolutionSetting ResolutionChangeEvent::NewResolution() const;

    private:
        ResolutionSetting m_Resolution;
    };

}
