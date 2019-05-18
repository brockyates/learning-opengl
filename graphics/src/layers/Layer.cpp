#include "pch.h"
#include "Layer.h"

namespace Graphics {

    Layer::Layer(Window* window, const std::string& name)
        : m_Window(window)
        , m_Name(name)
    {}
}
