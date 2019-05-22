#pragma once

#include "Layer.h"

namespace Graphics {

    //Used for testing and development if you need a no-op layer
    class PassthroughLayer : public Layer
    {
    public:
        PassthroughLayer(const Window& window, EventHandler<Event> eventCallback)
            : Layer(window, eventCallback, "Passthrough")
        {}

        virtual bool IsAttached() const override { return true; }
    };

}
