#pragma once

#include "ResolutionSetting.h"
#include "SmartGLFWWindow.h"
#include "WindowInput.h"
#include "WindowProperties.h"
#include "WindowedSettings.h"

#include "events/ChangeToWindowedEvent.h"
#include "events/Event.h"

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

        WindowedSettings GetWindowedSettings() { return m_WindowedSettings; }

        GLFWwindow* GetNativeWindow() const { return m_Window.get(); }

        //Setters
        void SetWindowedSettings(WindowedSettings settings) { m_WindowedSettings = settings; }
        void SetMode(WindowMode mode) { m_Properties.Mode = mode; }
        void SetResolution(ResolutionSetting resolution) { m_Properties.Resolution = resolution; }

    private:
        WindowedSettings InitializeWindowedSettings();

        //Event handlers
        EventHandler<ChangeToWindowedEvent> OnChangeToWindowed();

    private:
        WindowProperties m_Properties;
        SmartGLFWWindow m_Window;
        WindowedSettings m_WindowedSettings;

    public:
        WindowInput Input;
    };

}
