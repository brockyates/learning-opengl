#pragma once

namespace Graphics {

    struct WindowedSettings
    {
        WindowedSettings(int width, int  height, int  xpos, int  ypos)
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
