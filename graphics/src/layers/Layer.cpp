#include "pch.h"
#include "Layer.h"
#include <utility>

namespace Graphics {

    Layer::Layer(const Window& window, EventHandler<Event> eventCallback, std::string name)
        : window_(window)
        , name_(std::move(name))
        , eventCallback_(std::move(eventCallback))
    {}
}
