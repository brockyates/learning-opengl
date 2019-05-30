#include "pch.h"
#include "ResolutionChangeEvent.h"
#include <utility>

#include "EventType.h"

namespace Graphics {

    ResolutionChangeEvent::ResolutionChangeEvent(ResolutionSetting resolution)
        : m_Resolution(std::move(resolution))
    {}

    EventType ResolutionChangeEvent::Type() const
    {
        return GetStaticType();
    }

    EventType ResolutionChangeEvent::GetStaticType()
    {
        return EventType::ResolutionChangeEvent;
    }

    ResolutionSetting ResolutionChangeEvent::NewResolution() const
    {
        return m_Resolution;
    }

}
