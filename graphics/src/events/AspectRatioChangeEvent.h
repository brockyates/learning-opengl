#pragma once

#include "Event.h"

namespace Graphics
{
    class AspectRatioChangeEvent final : public Event
    {
    public:
        explicit AspectRatioChangeEvent(float aspectRatio);

        [[nodiscard]] EventType Type() const override;
        static EventType GetStaticType();

        [[nodiscard]] float NewAspectRatio() const;

    private:
        float aspectRatio_;
    };
}
