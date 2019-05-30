#pragma once

namespace graphics {

    struct WindowLayout
    {
        WindowLayout(int width, int  height, int  xpos, int  ypos, float aspectRatio);

        int Width;
        int Height;
        int Xpos;
        int Ypos;
        float WindowedAspectRatio;
    };

}
