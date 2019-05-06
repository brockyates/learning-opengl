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
        , m_Window(CreateGLFWWindow(m_WindowProperties))
        , m_UIRenderer(ImGuiRenderer(m_Window.get()))
    {
    }

    Application::~Application()
    {
        glfwTerminate();
        LOG_TRACE("~Application()");
    }

    void Application::Run()
    {
        {
            std::vector<Layer*> layerStack = {
                new BaseLayer(),
                new ImGuiLayer(),
                new MinimalTriangleDemo(),
            };

            LOG_INFO("Main application loop started");
            while (!glfwWindowShouldClose(m_Window.get()))
            {
                for (Layer* layer : layerStack)
                {
                    layer->OnUpdate();
                }

                m_UIRenderer.BeginFrame();
                for (Layer* layer : layerStack)
                {
                    layer->OnImGuiRender();
                }
                m_UIRenderer.Render(m_WindowProperties);

                glfwSwapBuffers(m_Window.get());
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
