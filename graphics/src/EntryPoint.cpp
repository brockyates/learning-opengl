#include "pch.h"
#include "Application.h"

int main()
{
    Utils::Log::Init();
    LOG_INFO("spdlog initialized");

    {
        Graphics::Application app;
        app.Run();
    }

    return 0;
}
