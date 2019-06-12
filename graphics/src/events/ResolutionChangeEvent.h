#pragma once

#include "Event.h"
#include "window/ResolutionSetting.h"

namespace Graphics
{
    class ResolutionChangeEvent final : public Event
    {
    public:
        explicit ResolutionChangeEvent(ResolutionSetting resolution);

        [[nodiscard]] EventType Type() const override;
        static EventType GetStaticType();

        [[nodiscard]] ResolutionSetting NewResolution() const;

    private:
        ResolutionSetting resolution_;
    };
}
