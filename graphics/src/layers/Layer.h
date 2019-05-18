#pragma once
#include <GLFW/glfw3.h>

#include "Window.h"

namespace Graphics {

    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        // Layers work with OpenGL global state and may have const members
        // I prefer that they're non-copyable, non-movable.
        Layer(Layer&) = delete;
        Layer(Layer&&) = delete;
        Layer& operator=(Layer&) = delete;
        Layer& operator=(Layer&&) = delete;

        virtual void RenderScene(Window* window) {}
        virtual void RenderUI(Window* window) {}

        virtual void Attach(Window* window) {};
        virtual void Detach(Window* window) {};
        virtual bool IsAttached() = 0;

        virtual std::string GetPopupText() const { return ""; }
        virtual std::string GetDescription() const { return ""; }

        inline const std::string& GetName() const { return m_Name; }

    protected:
        std::string m_Name;
    };

}
