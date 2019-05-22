#pragma once
#include <GLFW/glfw3.h>

#include "events/Event.h"
#include "Window.h"

namespace Graphics {

    class Layer
    {
    public:
        Layer(const Window& window, EventHandler<Event> eventCallback, const std::string& name = "Layer");
        virtual ~Layer() = default;

        // Layers work with OpenGL global state and may have const members
        // I prefer that they're non-copyable, non-movable.
        Layer(Layer&) = delete;
        Layer(Layer&&) = delete;
        Layer& operator=(Layer&) = delete;
        Layer& operator=(Layer&&) = delete;

        virtual void RenderScene() {}
        virtual void RenderUI() {}

        virtual void OnEvent(const Event& event) {};

        virtual void Attach() {};
        virtual void Detach() {};
        virtual bool IsAttached() const = 0;

        virtual std::string PopupText() const { return ""; }
        virtual std::string Description() const { return ""; }
        inline const std::string& Name() const { return m_Name; }

    protected:
        virtual void FireEvent(const Event& event) { m_EventCallback(event); }

    protected:
        const Window& m_Window;
        std::string m_Name;

    private:
        EventHandler<Event> m_EventCallback; //Private because we want the subclass to interface with FireEvent
    };

}
