#include "pch.h"
#include "Application.h"

int main()
{
    Graphics::Utils::Log::Init();
    LOG_INFO("spdlog initialized");

    {
        Graphics::Application::Run();
    }

    return 0;
}
