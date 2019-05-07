#include "pch.h"
#include "Application.h"

#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main()
{
    Graphics::Utils::Log::Init();

    {
        Graphics::Application().Start();
    }

    return 0;
}
