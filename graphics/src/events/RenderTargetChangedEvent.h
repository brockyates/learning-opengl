#pragma once

#include "Event.h"

namespace Graphics {

    class RenderTargetChangedEvent : public Event
    {
    public:
        RenderTargetChangedEvent(unsigned int nextRenderTargetID)
            : m_NextRenderTargetID(nextRenderTargetID)
        {}

        virtual EventType Type() const override { return GetStaticType(); }

        static EventType GetStaticType()
        {
            return EventType::RenderTargetChanged;
        }

        unsigned int RenderTargetChangedEvent::NextRenderTargetID() const { return m_NextRenderTargetID; }

    private:
        unsigned int m_NextRenderTargetID;
    };

}