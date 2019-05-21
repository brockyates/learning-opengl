#pragma once

#include "events/EventSystem.h"
#include "ResolutionSetting.h"
#include "SmartGLFWWindow.h"
#include "WindowInput.h"
#include "WindowProperties.h"
#include "WindowLayout.h"

namespace Graphics {

    class Window
    {
    public:
        Window();
        ~Window();

        void Update();
        void OnEvent(const Event& event);

        bool ShouldClose();
        bool IsFullscreen() const;

        int ResolutionWidth() const { return m_Properties.Resolution.Width; }
        int ResolutionHeight() const { return m_Properties.Resolution.Height; }
        float DefaultFontSize() const { return m_Properties.Resolution.DefaultFontSize; } //Used in ImGui initialization
        std::string DisplayName() const { return m_Properties.Title; }
        ResolutionSetting Resolution() const { return m_Properties.Resolution; }

        const WindowInput& Input() const { return m_Input; }
        GLFWwindow* GetNativeWindow() const { return m_Window.get(); } //Should only be needed for ImGui initialization

    private:
        //Event handlers
        EventHandler<ChangeResolutionEvent> OnResolutionChange();
        EventHandler<ChangeToWindowedEvent> OnChangeToWindowed();
        EventHandler<ChangeToFullscreenEvent> OnChangeToFullscreen();
        EventHandler<WindowCloseEvent> OnWindowClose();

    private:
        WindowProperties m_Properties;
        SmartGLFWWindow m_Window;
        WindowInput m_Input;
    };

}
