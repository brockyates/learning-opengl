#pragma once
#include "WindowProperties.h"

namespace Graphics
{
    class Application
    {
    public:
        Application();
        ~Application();

        Application(Application&) = delete;
        Application& operator=(Application&) = delete;

        void Start();

    private:
        WindowProperties m_WindowProperties;
    };

}
