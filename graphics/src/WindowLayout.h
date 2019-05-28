#pragma once

namespace Graphics {

    struct WindowLayout
    {
        WindowLayout(int width, int  height, int  xpos, int  ypos, float aspectRatio)
            : Width(width)
            , Height(height)
            , Xpos(xpos)
            , Ypos(ypos)
            , WindowedAspectRatio(aspectRatio)
        {}

        int Width;
        int Height;
        int Xpos;
        int Ypos;
        float WindowedAspectRatio;
    };

}
