#include "pch.h"
#include "Application.h"

#include "renderer/Renderer.h"

namespace Graphics {

    Application::~Application()
    {
        glfwTerminate();
        LOG_TRACE("~Application()");
    }

    void Application::Start()
    {
        Renderer renderer;

        LOG_INFO("Main application loop started");

        while (renderer.IsRunning())
        {
            renderer.OnRender();
        }

        LOG_INFO("Main application loop stopped");
    }

}
