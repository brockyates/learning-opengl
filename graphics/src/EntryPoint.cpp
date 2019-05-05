#include "pch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "imgui/ImGuiLayer.h"

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

void OnImGuiRender(Graphics::ImGuiLayer* imGuiLayer)
{
    bool my_tool_active = true;
    float my_color[] = { 0.0f, 1.0f, 0.0f, 1.0f };

    imGuiLayer->Begin();

    // Create a window called "My First Tool", with a menu bar.
    ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Edit a color (stored as ~4 floats)
    ImGui::ColorEdit4("Color", my_color);

    // Plot some values
    const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
    ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

    // Display contents in a scrolling region
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
    ImGui::BeginChild("Scrolling");
    for (int n = 0; n < 50; n++)
        ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();
    ImGui::End();

    imGuiLayer->End(1920, 1080);
}

int main()
{
    Utils::Log::Init();
    LOG_INFO("spdlog initialized");

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

    LOG_INFO(glGetString(GL_VERSION));

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

    std::string vertexShaderSource = ParseShader("res/shaders/minimal_v.shader");
    std::string fragmentShaderSource = ParseShader("res/shaders/minimal_f.shader");

    unsigned int shaderID = CreateShader(vertexShaderSource, fragmentShaderSource);
    glUseProgram(shaderID);

    Graphics::ImGuiLayer imGuiLayer;
    imGuiLayer.OnAttach(window);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderID);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        OnImGuiRender(&imGuiLayer);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    imGuiLayer.OnDetach();

    glfwTerminate();
    return 0;
}
