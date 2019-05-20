#pragma once

#include "ResolutionSetting.h"
#include "SmartGLFWWindow.h"
#include "WindowInput.h"
#include "WindowProperties.h"
#include "WindowedSettings.h"

#include "events/Events.h"

namespace Graphics {

    class Window
    {
    public:
        Window();
        ~Window();

        void Update();
        void OnEvent(Event& event);

        bool ShouldClose();
        bool IsFullscreen() const;

        int Width() const { return m_Properties.Resolution.Width; }
        int Height() const { return m_Properties.Resolution.Height; }
        float DefaultFontSize() const { return m_Properties.Resolution.DefaultFontSize; }
        std::string DisplayName() const { return m_Properties.Title; }
        ResolutionSetting Resolution() const { return m_Properties.Resolution; }

        GLFWwindow* GetNativeWindow() { return m_Window.get(); } //Should only be needed for ImGui initialization

    private:
        WindowedSettings InitializeWindowedSettings();

        //Event handlers
        EventHandler<ChangeResolutionEvent> OnResolutionChange();
        EventHandler<ChangeToWindowedEvent> OnChangeToWindowed();
        EventHandler<ChangeToFullscreenEvent> OnChangeToFullscreen();
        EventHandler<WindowCloseEvent> OnWindowClose();

    private:
        WindowProperties m_Properties;
        SmartGLFWWindow m_Window;
        WindowedSettings m_WindowedSettings;

    public:
        WindowInput Input;
    };

}
