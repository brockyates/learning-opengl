#include "pch.h"
#include "Layer.h"

namespace Graphics {

    Layer::Layer(WindowContext* window, const std::string& name)
        : m_Name(name)
        , m_Window(window)
    {}
}
