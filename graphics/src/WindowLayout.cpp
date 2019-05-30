#include "pch.h"
#include "WindowLayout.h"

namespace graphics {

    WindowLayout::WindowLayout(int width, int  height, int  xpos, int  ypos, float aspectRatio)
        : Width(width)
        , Height(height)
        , Xpos(xpos)
        , Ypos(ypos)
        , WindowedAspectRatio(aspectRatio)
    {}

}
