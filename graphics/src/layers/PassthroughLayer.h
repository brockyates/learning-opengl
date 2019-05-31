#pragma once

#include "events/Event.h"

#include "Layer.h"

namespace Graphics {

    class Window;

    //Used for testing and development if you need a no-op layer
    class PassthroughLayer final : public Layer
    {
    public:
        PassthroughLayer(const Window& window, EventHandler<Event> eventCallback);

        [[nodiscard]] bool IsAttached() const override;
    };

}
