#pragma once

#include <GLFW/glfw3.h>

namespace Graphics {

    class ImGuiLayer
    {
    public:
        void OnAttach(GLFWwindow* window);
        void OnDetach();

        void Begin();
        void End(unsigned int width, unsigned int height);

    private:
        float m_Time = 0.0f;
    };

}
