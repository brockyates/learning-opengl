#include "pch.h"

#include "Application.h"
#include "logging/Log.h"

//Hide console window
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main()
{
    Graphics::Utils::Log::Init();
    Graphics::Application().Start();

    return 0;
}
