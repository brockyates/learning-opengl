#pragma once
#include "imgui/ImGuiRenderer.h"
#include "SmartGLFWWindow.h"
#include "WindowProperties.h"

namespace Graphics
{
    class Application
    {
    public:
        Application();
        ~Application();

        Application(Application&) = delete;
        Application(Application&&) = delete;

        void Run();

    private:
        WindowProperties m_WindowProperties;
        SmartGLFWWindow m_Window;
        ImGuiRenderer m_UIRenderer;
    };

}
