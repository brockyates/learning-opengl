#pragma once

#include "Event.h"

namespace Graphics {

    class RenderTargetChangeEvent : public Event
    {
    public:
        RenderTargetChangeEvent(unsigned int nextRenderTargetID);

        [[nodiscard]] virtual EventType Type() const override;
        static EventType GetStaticType();

        [[nodiscard]] unsigned int RenderTargetChangeEvent::NextRenderTargetID() const;

    private:
        unsigned int m_NextRenderTargetID;
    };

}