#include "pch.h"
#include "Application.h"

int main()
{
    Graphics::Utils::Log::Init();

    {
        Graphics::Application().Run();
    }

    return 0;
}
