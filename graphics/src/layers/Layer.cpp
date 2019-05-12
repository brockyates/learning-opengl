#include "pch.h"
#include "Layer.h"

namespace Graphics {

    Layer::Layer(const WindowContext* window, const std::string& name)
        : m_Name(name)
        , m_Window(window)
    {}

    void Layer::ChangeContext(const WindowContext * window)
    {
        m_Window = window;
    }

}
