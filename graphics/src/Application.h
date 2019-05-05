#pragma once
#include <GLFW/glfw3.h>
namespace Graphics
{

    class Application
    {
    public:
        Application();
        ~Application();
        void Run();

    private:
        static GLFWwindow* CreateApplicationWindow();
    };

}
