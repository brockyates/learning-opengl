#pragma once
#include <GLFW/glfw3.h>

#include "WindowContext.h"

namespace Graphics {

    class Layer
    {
    public:
        Layer(WindowContext* window, const std::string& name = "Layer");
        virtual ~Layer() = default;

        // Layers work with OpenGL global state and may have const members
        // I prefer that they're non-copyable, non-movable.
        Layer(Layer&) = delete;
        Layer(Layer&&) = delete;
        Layer& operator=(Layer&) = delete;
        Layer& operator=(Layer&&) = delete;

        virtual void OnUpdate() {}
        virtual void OnImGuiRender() {}

        virtual void Attach() {};
        virtual void Detach() {};
        virtual bool IsAttached() = 0;

        virtual std::string GetPopupText() const { return ""; }
        virtual std::string GetDescription() const { return ""; }

        inline const std::string& GetName() const { return m_Name; }

    protected:
        std::string m_Name;
        WindowContext* m_Window;
    };

}
