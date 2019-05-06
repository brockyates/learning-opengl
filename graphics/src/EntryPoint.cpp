#include "pch.h"
#include "Application.h"

int main()
{
    Graphics::Utils::Log::Init();

    {
        Graphics::Application().Start();
    }

    return 0;
}
