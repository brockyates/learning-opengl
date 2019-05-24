#pragma once

#include <GLFW/glfw3.h>

namespace Graphics {

    class Time
    {
    public:
        static double Get() { return glfwGetTime(); }
    };

}
