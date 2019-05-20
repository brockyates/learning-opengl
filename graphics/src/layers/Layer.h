#pragma once
#include <GLFW/glfw3.h>

#include "events/Event.h"
#include "Window.h"

namespace Graphics {

    class Layer
    {
    public:
        Layer(Window* window, EventHandler<Event> eventCallback, const std::string& name = "Layer");
        virtual ~Layer() = default;

        // Layers work with OpenGL global state and may have const members
        // I prefer that they're non-copyable, non-movable.
        Layer(Layer&) = delete;
        Layer(Layer&&) = delete;
        Layer& operator=(Layer&) = delete;
        Layer& operator=(Layer&&) = delete;

        virtual void RenderScene() {}
        virtual void RenderUI() {}

        virtual void OnEvent(Event& event) {};

        virtual void Attach() {};
        virtual void Detach() {};
        virtual bool IsAttached() = 0;

        virtual std::string GetPopupText() const { return ""; }
        virtual std::string GetDescription() const { return ""; }

        inline const std::string& GetName() const { return m_Name; }

    protected:
        virtual void FireEvent(Event& event) { m_EventCallback(event); }

    protected:
        Window* m_Window;
        std::string m_Name;

    private:
        EventHandler<Event> m_EventCallback; //Private because we want the subclass to interface with FireEvent
    };

}
