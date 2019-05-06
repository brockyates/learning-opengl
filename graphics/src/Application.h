#pragma once
#include "SmartGLFWWindow.h"

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
        SmartGLFWWindow m_Window;
    };

}
