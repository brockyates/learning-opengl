#include "pch.h"
#include "RenderToTexture.h"
#include "ShaderHelpers.h"

#include "WindowProperties.h"

#include <glad/glad.h>
#include <imgui.h>

namespace Graphics {

    RenderToTexture::RenderToTexture(const WindowProperties& windowProperties)
        : m_WindowProperties(windowProperties)
        , Layer("Render to Texture")
    {}

    void RenderToTexture::OnUpdate()
    {
        if (!m_Attached)
            return;

        // Bindings
        glBindVertexArray(m_VertexArrayID);
        glUseProgram(m_ShaderID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

        // Draw
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
        glViewport(0, 0, 800, 600);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Release bindings
        glUseProgram(0);
        glBindVertexArray(0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void RenderToTexture::OnImGuiRender()
    {
        if (!m_Attached)
            return;

        ImGui::Begin("Scene");

        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddImage(
            (void *)(intptr_t)m_RenderedTextureID,
            ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + 800 / 2, ImGui::GetCursorScreenPos().y + 800 / 2),
            ImVec2(0, 1),
            ImVec2(1, 0));

        ImGui::End();

        ImGui::Begin("Demos");

        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::TextWrapped(GetDescription().c_str());
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
        ImGui::Separator();
        ImGui::ColorEdit4("glClearColor", &m_ClearColor[0]);

        ImGui::End();
    }

    void RenderToTexture::Attach()
    {
        if (m_Attached) return;

        LOG_TRACE("Attaching RenderToTexture");

        glGenFramebuffers(1, &m_FrameBufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferID);

        glGenTextures(1, &m_RenderedTextureID);
        glBindTexture(GL_TEXTURE_2D, m_RenderedTextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderedTextureID, 0);

        glGenRenderbuffers(1, &m_RenderBufferID);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferID);

        const unsigned int frameBufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (!(frameBufferStatus == GL_FRAMEBUFFER_COMPLETE))
        {
            LOG_GL_ERROR([&]() {
                std::stringstream ss;
                ss << "Framebuffer status error. Status: " << std::hex << frameBufferStatus;
                return ss.str();
            }());
        }
        else
        {
            LOG_GL_TRACE("Framebuffer complete");
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glGenVertexArrays(1, &m_VertexArrayID);
        glBindVertexArray(m_VertexArrayID);
        glGenBuffers(1, &m_VertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, std::size(m_Vertexes) * sizeof(float), &m_Vertexes[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        m_ShaderID = CreateShader("res/shaders/Minimal_Vertex.shader", "res/shaders/Minimal_Fragment.shader");

        m_Attached = true;
    }

    void RenderToTexture::Detach()
    {
        if (!m_Attached) return;

        LOG_TRACE("Detaching RenderToTexture");

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glDeleteProgram(m_ShaderID);
        glDeleteBuffers(1, &m_VertexBufferID);
        glDeleteFramebuffers(1, &m_FrameBufferID);

        m_Attached = false;
    }

    std::string RenderToTexture::GetPopupText() const
    {
        return "Render to texture and present image in scene window";
    }

    std::string RenderToTexture::GetDescription() const
    {
        return "Render to texture draws a scene to the frame buffer, renders it to a texture, and displays the resulting image in the ImGui scene window.";
    }

}
