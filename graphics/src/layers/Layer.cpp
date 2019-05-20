#include "pch.h"
#include "Layer.h"

namespace Graphics {

    Layer::Layer(Window* window, EventHandler<Event> eventCallback, const std::string& name)
        : m_Window(window)
        , m_EventCallback(eventCallback)
        , m_Name(name)
    {}
}
