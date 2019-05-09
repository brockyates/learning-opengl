#include "pch.h"
#include "Application.h"

#include "renderer/Window.h"

namespace Graphics {

    Application::~Application()
    {
        glfwTerminate();
    }

    void Application::Start()
    {
        Window renderer;

        LOG_INFO("Main application loop started");

        try {
            while (renderer.IsRunning())
            {
                renderer.OnRender();
            }
        }
        catch (...)
        {
            std::cout << "TOP LEVEL ERROR HANDLER";
        }

        LOG_INFO("Main application loop stopped");
    }

}
