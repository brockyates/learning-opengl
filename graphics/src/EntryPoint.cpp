#include "pch.h"
#include "Application.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main()
{
    Graphics::Utils::Log::Init();

    Graphics::Application application;

    {
        application.Start();
    }

    return 0;
}
