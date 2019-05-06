#include "pch.h"
#include "Application.h"

#include "imgui/ImGuiRenderer.h"
#include "LayerManager.h"
#include "Layer.h"
#include "Shader.h"
#include "SmartGLFWWindow.h"

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
            auto layers = LayerManager();

            LOG_INFO("Main application loop started");
            while (!glfwWindowShouldClose(window.get()))
            {
                for (auto& layer : layers)
                {
                    layer->OnUpdate();
                }

                uiRenderer.BeginFrame();
                for (auto& layer : layers)
                {
                    layer->OnImGuiRender();
                }
                uiRenderer.Render(m_WindowProperties);

                glfwSwapBuffers(window.get());
                glfwPollEvents();
            }

            LOG_INFO("Main application loop stopped");
        } //Application scope
    }

}
