#include "pch.h"
#include "Application.h"

#include "Window.h"

namespace Graphics {

    void Application::Start()
    {
        Window window;

        LOG_INFO("Main application loop started");

        while (!window.ShouldClose())
        {
            window.OnUpdate();
        }

        LOG_INFO("Main application loop stopped");
    }

}
