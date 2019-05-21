#pragma once

namespace Graphics {

    struct WindowLayout
    {
        WindowLayout(int width, int  height, int  xpos, int  ypos)
            : Width(width)
            , Height(height)
            , Xpos(xpos)
            , Ypos(ypos)
        {}

        int Width;
        int Height;
        int Xpos;
        int Ypos;
    };

}
