#pragma once

#include "events/AspectRatioChangeEvent.h"
#include "events/ChangeToFullscreenEvent.h"
#include "events/ChangeToWindowedEvent.h"
#include "events/ResolutionChangeEvent.h"
#include "events/WindowCloseEvent.h"

#include "ResolutionSetting.h"
#include "SmartGLFWWindow.h"
#include "WindowInput.h"
#include "WindowProperties.h"

namespace Graphics
{
    class Window
    {
    public:
        explicit Window(EventHandler<Event> eventCallback);

        ~Window();
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = default;
        Window& operator=(Window&&) = default;

        void Update() const;
        void OnEvent(const Event&);

        [[nodiscard]] bool ShouldClose() const;
        [[nodiscard]] bool IsFullscreen() const;

        [[nodiscard]] int ResolutionWidth() const { return properties_.Resolution.Width; }
        [[nodiscard]] int ResolutionHeight() const { return properties_.Resolution.Height; }
        [[nodiscard]] float AspectRatio() const { return properties_.AspectRatio; }

        //Used in ImGui initialization
        [[nodiscard]] float DefaultFontSize() const { return properties_.Resolution.DefaultFontSize; }

        [[nodiscard]] std::string DisplayName() const { return properties_.Title; }
        [[nodiscard]] ResolutionSetting Resolution() const { return properties_.Resolution; }

        [[nodiscard]] const WindowInput& Input() const { return input_; }

        //Should only be needed for ImGui initialization
        [[nodiscard]] GLFWwindow* GetNativeWindow() const { return window_.get(); }

    private:
        //Event handlers
        void FireEvent(const Event& event) const { eventCallback_(event); }

        EventHandler<AspectRatioChangeEvent> OnAspectRatioChange();
        EventHandler<ResolutionChangeEvent> OnResolutionChange();
        EventHandler<ChangeToWindowedEvent> OnChangeToWindowed();
        EventHandler<ChangeToFullscreenEvent> OnChangeToFullscreen();
        EventHandler<WindowCloseEvent> OnWindowClose();

        WindowProperties properties_;
        SmartGlfwWindow window_;
        WindowInput input_;
        EventHandler<Event> eventCallback_;
    };
}
