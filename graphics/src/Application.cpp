#include "pch.h"
#include "Application.h"
#include "Layer.h"
#include "Shader.h"

#include "imgui/ImGuiRenderer.h"

//Layers
#include "layers/BaseLayer.h"
#include "layers/ImGuiLayer.h"
#include "layers/MinimalTriangleDemo.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

namespace Graphics
{
    GLFWwindow* Application::CreateApplicationWindow()
    {
        /* Initialize the library */
        bool glfwInitStatus = glfwInit();
        APP_ASSERT(glfwInitStatus, "Failed to initialize GLFW");

        /* Create a windowed mode window and its OpenGL context */
        GLFWwindow* window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            APP_ASSERT(window, "Failed to create GLFW window");
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
        int gladLoadStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!gladLoadStatus)
        {
            glfwTerminate();
            APP_ASSERT(gladLoadStatus, "Failed to initialize Glad");
        }

        LOG_GL_INFO(glGetString(GL_VERSION));
        return window;
    }

    void Application::Run()
    {
        { //Application scope
            GLFWwindow* window = CreateApplicationWindow();
            ImGuiRenderer imGuiRenderer(window);

            std::vector<Layer*> layerStack = {
                new BaseLayer(),
                new ImGuiLayer(),
                new MinimalTriangleDemo(),
            };

            LOG_INFO("Main application loop started");
            while (!glfwWindowShouldClose(window))
            {
                for (Layer* layer : layerStack)
                {
                    layer->OnUpdate();
                }

                ImGuiRenderer::BeginFrame();
                for (Layer* layer : layerStack)
                {
                    layer->OnImGuiRender();
                }
                ImGuiRenderer::Render(1920, 1080);

                glfwSwapBuffers(window);
                glfwPollEvents();
            }
            LOG_INFO("Main application loop stopped");

            for (auto layer : layerStack)
            {
                delete layer;
            }

        } //Application scope

        glfwTerminate();
    }

}
