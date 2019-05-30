#include "pch.h"

#include "logging/Log.h"

#include "Application.h"

//Hide console window
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main()
{
    graphics::utils::Log::Init();
    graphics::Application().Start();

    return 0;
}
