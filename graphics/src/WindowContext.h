#pragma once

#include "WindowInput.h"
#include "WindowProperties.h"

namespace Graphics {

    struct WindowContext
    {
        WindowContext(GLFWwindow* window, WindowProperties properties)
            : Properties(properties)
            , Input(window)
            , Window(window)
        {}

        WindowProperties Properties;
        WindowInput Input;
        GLFWwindow* Window;
    };

}
