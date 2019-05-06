#pragma once

namespace Graphics
{
    class Application
    {
    public:
        Application() = default;
        ~Application();

        Application(Application&) = delete;
        Application& operator=(Application&) = delete;

        void Start();
    };

}
