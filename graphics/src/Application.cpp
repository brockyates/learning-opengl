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
    Application::Application()
    {
        Graphics::Utils::Log::Init();
        m_Window = CreateGLFWWindow(); // Don't put in the initialization list: needs logging to be initialized.
    }

    Application::~Application()
    {
        glfwTerminate();
        LOG_TRACE("~Application()");
    }

    void Application::Run()
    {
        {
            ImGuiRenderer imGuiRenderer(m_Window.get());

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

                ImGuiRenderer::BeginFrame();
                for (Layer* layer : layerStack)
                {
                    layer->OnImGuiRender();
                }
                ImGuiRenderer::Render(1920, 1080);

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
