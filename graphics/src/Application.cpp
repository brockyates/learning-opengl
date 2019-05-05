#include "pch.h"
#include "Application.h"
#include "Layer.h"
#include "Shader.h"

#include "imgui/ImGuiRenderer.h"
#include "layers/ImGuiLayer.h"

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

            float m_Vertexes[] =
            {
                0.0f,  1.0f,
               -1.0f, -1.0f,
                1.0f, -1.0f,
            };

            unsigned int myBufferID;
            glGenBuffers(1, &myBufferID);
            glBindBuffer(GL_ARRAY_BUFFER, myBufferID);
            glBufferData(GL_ARRAY_BUFFER, std::size(m_Vertexes) * sizeof(float), &m_Vertexes, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

            Shader minimalShader("res/shaders/Minimal_Vertex.shader", "res/shaders/Minimal_Fragment.shader");

            ImGuiRenderer imGuiRenderer(window);

            Layer* imGuiLayer = new ImGuiLayer();
            std::vector<Layer*> layerStack = { imGuiLayer };

            LOG_INFO("Main application loop started");
            while (!glfwWindowShouldClose(window))
            {
                glClear(GL_COLOR_BUFFER_BIT);
                glClearColor(0.2f, 0.3f, 0.7f, 1.0f);

                minimalShader.Bind();
                glDrawArrays(GL_TRIANGLES, 0, 3);

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
