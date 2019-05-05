#pragma once
#include <GLFW/glfw3.h>
namespace Graphics
{

    class Application
    {
    public:
        static void Run();

    private:
        static GLFWwindow* CreateApplicationWindow();
    };

}
