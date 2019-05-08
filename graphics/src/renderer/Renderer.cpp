#include "pch.h"
#include "Renderer.h"

#include "renderer/Layer.h"

#include <filesystem>

namespace Graphics {

    void GLAPIENTRY
        MessageCallback(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam)
    {
        std::stringstream ss;
        ss << "OpenGL Debug Callback: " << type << " type=" << std::hex << type << ", severity=" << std::hex << severity << ", message: " << message;

        LOG_ERROR(ss.str());

#define LOGNAME_FORMAT "%Y%m%d_%H%M%S"
#define LOGNAME_SIZE 20

        std::time_t t = std::time(nullptr);
        static char name[LOGNAME_SIZE];
        strftime(name, sizeof(name), LOGNAME_FORMAT, localtime(&t));

        std::stringstream ss2;
        ss2 << "../bin/logs/GraphicsLog" << name << ".txt";

        std::filesystem::create_directory("../bin/logs");
        std::ofstream file(ss2.str(), std::ios::binary);
        file << Graphics::Utils::Log::GetLogStream().str();
        file.close();

        APP_ASSERT(false, "Exiting due to OpenGL error...");
    }

    Renderer::Renderer()
        : m_WindowProperties("OpenGL Graphics Demo", 1920, 1080)
        , m_Window(CreateGLFWWindow(m_WindowProperties))
        , m_UIRenderer(ImGuiRenderer(m_Window.get()))
        , m_Layers(m_Window.get())
    {
#ifdef APP_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);
#endif
    }

    void Renderer::OnRender()
    {
        RenderScene();
        RenderUIElements();

        glfwSwapBuffers(m_Window.get());
        glfwPollEvents();
    }

    bool Renderer::IsRunning() const
    {
        return !glfwWindowShouldClose(m_Window.get());
    }

    void Renderer::RenderScene()
    {
        for (auto& layer : m_Layers)
        {
            layer->OnRender();
        }
    }

    void Renderer::RenderUIElements()
    {
        m_UIRenderer.BeginFrame();
        for (auto& layer : m_Layers)
        {
            layer->OnImGuiRender();
        }
        m_UIRenderer.Render(m_WindowProperties);
    }

}
