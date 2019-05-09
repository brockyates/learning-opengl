#pragma once
#include <GLFW/glfw3.h>

namespace Graphics {

    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnRender() {}
        virtual void OnImGuiRender() {}

        inline const std::string& GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };

}
