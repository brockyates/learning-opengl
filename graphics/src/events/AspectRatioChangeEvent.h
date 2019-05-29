#pragma once

#include "Event.h"

namespace Graphics {

    class AspectRatioChangeEvent : public Event
    {
    public:
        AspectRatioChangeEvent(float aspectRatio);

        virtual EventType Type() const override;
        static EventType GetStaticType();

        float AspectRatioChangeEvent::NewAspectRatio() const;

    private:
        float m_AspectRatio;
    };

}
