#pragma once

#include "WindowInput.h"
#include "WindowProperties.h"

namespace Graphics {

    struct WindowContext
    {
        WindowProperties Properties;
        WindowInput Input;
    };

}
