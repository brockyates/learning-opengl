#pragma once

#include "config/WindowConfig.h"
#include "SmartGLFWWindow.h"
#include "WindowInput.h"
#include "WindowProperties.h"

namespace Graphics {

    struct WindowContext
    {
        WindowContext()
            : m_Window(CreateInitialWindowedGLFWWindow(WindowConfig::Properties))
            , Properties(WindowConfig::Properties)
            , Input(NativeWindow())
        {}

    private:
        SmartGLFWWindow m_Window;

    public:
        GLFWwindow* NativeWindow() { return m_Window.get(); }
        const GLFWwindow* NativeWindow() const { return m_Window.get(); }

        WindowProperties Properties;
        WindowInput Input;
    };

}
