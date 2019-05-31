#pragma once

#include "events/Event.h"

namespace Graphics {

    class Window;

    class Layer
    {
    public:
        Layer(const Window& window, EventHandler<Event> eventCallback, std::string name = "Layer");
        virtual ~Layer() = default;

        // Layers work with OpenGL global state and may have const members
        // I prefer that they're non-copyable, non-movable.
        Layer(Layer&) = delete;
        Layer(Layer&&) = delete;

        Layer& operator=(Layer&) = delete;
        Layer& operator=(Layer&&) = delete;

        virtual void RenderScene() {}
        virtual void RenderUi() {}

        virtual void OnEvent(const Event&) {};

        virtual void Attach() {};
        virtual void Detach() {};
        [[nodiscard]] virtual bool IsAttached() const = 0;

        [[nodiscard]] virtual std::string PopupText() const { return ""; }
        [[nodiscard]] virtual std::string Description() const { return ""; }
        [[nodiscard]] const std::string& Name() const { return name_; }

    protected:
        virtual void FireEvent(const Event& event) { eventCallback_(event); }

        const Window& window_;
        std::string name_;

    private:
        EventHandler<Event> eventCallback_; //Private because we want the subclass to interface with FireEvent
    };

}
