#include "pch.h"
#include "PassthroughLayer.h"
#include <utility>

#include "Window.h"

namespace Graphics {

    PassthroughLayer::PassthroughLayer(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, std::move(eventCallback), "Passthrough")
    {}

    bool PassthroughLayer::IsAttached() const
    {
        return true;
    }

}
