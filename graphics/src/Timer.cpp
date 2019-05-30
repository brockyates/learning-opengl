#include "pch.h"
#include "Timer.h"

#include <GLFW/glfw3.h>

namespace graphics {

    double Timer::Get() { return glfwGetTime(); }

}
