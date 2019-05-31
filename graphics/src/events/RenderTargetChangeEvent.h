#pragma once

#include "Event.h"

namespace Graphics {

    class RenderTargetChangeEvent final : public Event
    {
    public:
        explicit RenderTargetChangeEvent(unsigned int nextRenderTargetId);

        [[nodiscard]] EventType Type() const override;
        static EventType GetStaticType();

        [[nodiscard]] unsigned int NextRenderTargetId() const;

    private:
        unsigned int nextRenderTargetId_;
    };

}