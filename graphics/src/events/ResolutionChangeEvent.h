#pragma once

#include "Event.h"
#include "ResolutionSetting.h"

namespace Graphics {

    class ResolutionChangeEvent : public Event
    {
    public:
        ResolutionChangeEvent(ResolutionSetting resolution);

        [[nodiscard]] virtual EventType Type() const override;
        static EventType GetStaticType();

        [[nodiscard]] ResolutionSetting ResolutionChangeEvent::NewResolution() const;

    private:
        ResolutionSetting m_Resolution;
    };

}
