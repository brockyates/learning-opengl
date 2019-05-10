#pragma once
#include <GLFW/glfw3.h>

namespace Graphics {

    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnUpdate() {}
        virtual void OnImGuiRender() {}

        virtual void Attach() {};
        virtual void Detach() {};

        virtual bool IsAttached() = 0;

        inline const std::string& GetName() const { return m_Name; }

    protected:
        std::string m_Name;
    };

}
