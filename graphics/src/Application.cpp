#include "pch.h"
#include "Application.h"
#include "Layer.h"

#include "imgui/ImGuiRenderer.h"

#include "layers/ImGuiLayer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

namespace Graphics
{
    std::string ParseShader(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (file.fail()) {
            LOG_ERROR([&]()
            {
                std::stringstream ss;
                ss << "Can't open shader file: " << filePath << ". Does the file exist?";
                return ss.str();
            }());
        }
        std::stringstream ss;
        ss << file.rdbuf();

        return ss.str();
    }

    unsigned int CompileShader(unsigned int type, const std::string& shaderSource)
    {
        unsigned int shaderId = glCreateShader(type);
        const char* source = shaderSource.c_str();
        glShaderSource(shaderId, 1, &source, nullptr);
        glCompileShader(shaderId);

        int result;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(shaderId, length, &length, message);

            std::stringstream ss;
            ss << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader";
            LOG_ERROR(ss.str());
            LOG_ERROR(message);

            glDeleteShader(shaderId);
            return 0;
        }

        return shaderId;
    }

    unsigned int CreateShader(const std::string& vertexShaderSource,
        const std::string& fragmentShaderSource)
    {
        unsigned int program = glCreateProgram();
        unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
        unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }

    GLFWwindow* CreateAppWindow()
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
        GLFWwindow* window = CreateAppWindow();

        glClearColor(0.2f, 0.3f, 0.7f, 1.0f);

        float m_Vertexes[] =
        {
            0.0f,  1.0f,
           -1.0f, -1.0f,
            1.0f, -1.0f,
        };

        std::stringstream ss;
        ss << std::size(m_Vertexes);
        LOG_INFO(ss.str());

        unsigned int myBufferID;
        glGenBuffers(1, &myBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, myBufferID);
        glBufferData(GL_ARRAY_BUFFER, std::size(m_Vertexes) * sizeof(float), &m_Vertexes, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

        std::string vertexShaderSource = ParseShader("res/shaders/Minimal_Vertex.shader");
        std::string fragmentShaderSource = ParseShader("res/shaders/Minimal_Fragment.shader");

        unsigned int shaderID = CreateShader(vertexShaderSource, fragmentShaderSource);
        glUseProgram(shaderID);

        Layer* imGuiLayer = new ImGuiLayer();
        std::vector<Layer*> layerStack = { imGuiLayer };

        for (auto layer : layerStack)
        {
            layer->OnAttach(window);
        }

        LOG_INFO("Main application loop started");
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shaderID);
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
            layer->OnDetach();
            delete layer;
        }

        glfwTerminate();
    }
}
