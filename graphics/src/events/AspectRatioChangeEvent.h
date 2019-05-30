#pragma once

#include "Event.h"

namespace Graphics {

    class AspectRatioChangeEvent : public Event
    {
    public:
        AspectRatioChangeEvent(float aspectRatio);

        [[nodiscard]] EventType Type() const override;
        static EventType GetStaticType();

        [[nodiscard]] float NewAspectRatio() const;

    private:
        float m_AspectRatio;
    };

}
