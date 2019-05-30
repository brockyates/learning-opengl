#include "pch.h"
#include "Layer.h"
#include <utility>

namespace Graphics {

    Layer::Layer(const Window& window, EventHandler<Event> eventCallback, const std::string& name)
        : m_Window(window)
        , m_EventCallback(std::move(eventCallback))
        , m_Name(name)
    {}
}
