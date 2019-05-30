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

namespace Graphics {

    class Window
    {
    public:
        Window(EventHandler<Event> eventCallback);
        ~Window();

        void Update();
        void OnEvent(const Event&);

        bool ShouldClose();
        [[nodiscard]] bool IsFullscreen() const;

        [[nodiscard]] int ResolutionWidth() const { return m_Properties.Resolution.Width; }
        [[nodiscard]] int ResolutionHeight() const { return m_Properties.Resolution.Height; }
        [[nodiscard]] float AspectRatio() const { return m_Properties.AspectRatio; }

        [[nodiscard]] float DefaultFontSize() const { return m_Properties.Resolution.DefaultFontSize; } //Used in ImGui initialization
        [[nodiscard]] std::string DisplayName() const { return m_Properties.Title; }
        [[nodiscard]] ResolutionSetting Resolution() const { return m_Properties.Resolution; }

        [[nodiscard]] const WindowInput& Input() const { return m_Input; }
        [[nodiscard]] GLFWwindow* GetNativeWindow() const { return m_Window.get(); } //Should only be needed for ImGui initialization

    private:
        //Event handlers
        void FireEvent(const Event& event) { m_EventCallback(event); }

        EventHandler<AspectRatioChangeEvent> OnAspectRatioChange();
        EventHandler<ResolutionChangeEvent> OnResolutionChange();
        EventHandler<ChangeToWindowedEvent> OnChangeToWindowed();
        EventHandler<ChangeToFullscreenEvent> OnChangeToFullscreen();
        EventHandler<WindowCloseEvent> OnWindowClose();

    private:
        WindowProperties m_Properties;
        SmartGLFWWindow m_Window;
        WindowInput m_Input;
        EventHandler<Event> m_EventCallback;
    };

}
