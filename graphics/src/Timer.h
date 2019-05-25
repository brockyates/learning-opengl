#pragma once

#include <GLFW/glfw3.h>

namespace Graphics {

    class Timer
    {
    public:
        static double Get() { return glfwGetTime(); }
    };

}
