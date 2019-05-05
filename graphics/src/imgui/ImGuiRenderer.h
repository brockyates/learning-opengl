#pragma once

namespace Graphics {

    class ImGuiRenderer
    {
    public:
        static void BeginFrame();
        static void Render(unsigned int height, unsigned int width);
    };

}
