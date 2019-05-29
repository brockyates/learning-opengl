#include "pch.h"
#include "PassthroughLayer.h"

#include "Window.h"

namespace Graphics {

    PassthroughLayer::PassthroughLayer(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, eventCallback, "Passthrough")
    {}

    bool PassthroughLayer::IsAttached() const
    {
        return true;
    }

}
