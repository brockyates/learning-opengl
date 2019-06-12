#include "pch.h"
#include "Timer.h"

#include <GLFW/glfw3.h>

namespace Graphics
{
    double Timer::Get() { return glfwGetTime(); }
}
