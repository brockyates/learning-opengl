#pragma once

#include "WindowContext.h"
#include "WindowedSettings.h"

namespace Graphics {

    class Window
    {
    public:
        Window();
        ~Window();

        void Update();

        bool ShouldClose();
        bool IsFullscreen() const;

        int Width() const { return m_Context.Properties.Resolution.Width; }
        int Height() const { return m_Context.Properties.Resolution.Height; }

        WindowContext* Context() { return &m_Context; }
        WindowedSettings GetWindowedSettings() { return m_WindowedSettings; }
        void SetWindowedSettings(WindowedSettings settings) { m_WindowedSettings = settings; }

    private:
        WindowedSettings InitializeWindowedSettings();

    private:
        WindowContext m_Context;
        WindowedSettings m_WindowedSettings;
    };

}
