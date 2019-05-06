#include "pch.h"
#include "Application.h"
#include "Layer.h"
#include "Shader.h"

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
    Application::Application()
        : m_WindowProperties("OpenGL Graphics Demo", 1920, 1080)
    {
    }

    Application::~Application()
    {
        glfwTerminate();
        LOG_TRACE("~Application()");
    }

    void Application::Start()
    {
        {
            auto window = CreateGLFWWindow(m_WindowProperties);
            auto uiRenderer = ImGuiRenderer(window.get());

            std::vector<Layer*> layerStack = {
                new BaseLayer(),
                new ImGuiLayer(),
                new MinimalTriangleDemo(),
            };

            LOG_INFO("Main application loop started");
            while (!glfwWindowShouldClose(window.get()))
            {
                for (Layer* layer : layerStack)
                {
                    layer->OnUpdate();
                }

                uiRenderer.BeginFrame();
                for (Layer* layer : layerStack)
                {
                    layer->OnImGuiRender();
                }
                uiRenderer.Render(m_WindowProperties);

                glfwSwapBuffers(window.get());
                glfwPollEvents();
            }
            LOG_INFO("Main application loop stopped");

            for (auto layer : layerStack)
            {
                delete layer;
            }

        } //Application scope
    }

}
