#include "pch.h"
#include "RenderTargetLayer.h"

#include "events/EventDispatcher.h"
#include "MathHelpers.h"
#include "ShaderHelpers.h"
#include "WindowProperties.h"

#include <glad/glad.h>
#include <imgui.h>

namespace Graphics {

    RenderTargetLayer::RenderTargetLayer(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, eventCallback, "Render to Texture")
        , m_AspectRatio(window.AspectRatio())
    {
        Attach();
        FireEvent(RenderTargetChangeEvent(m_WindowedRenderTargetID));
    }

    RenderTargetLayer::~RenderTargetLayer()
    {
        Detach();
    }

    void RenderTargetLayer::RenderUI()
    {
        HandleAspectRatioChange();

        ImGui::Begin("Scene");
        ImVec2 pos = ImGui::GetCursorScreenPos();
        auto size = ImGui::GetContentRegionAvail();

        ImGui::GetWindowDrawList()->AddImage(
            (void *)(intptr_t)m_RenderedTextureID,
            ImVec2(ImGui::GetCursorScreenPos()),
            ImVec2(ImGui::GetCursorScreenPos().x + size.x, ImGui::GetCursorScreenPos().y + size.y),
            ImVec2(0, 1),
            ImVec2(1, 0));
        ImGui::End();
    }

    void RenderTargetLayer::OnEvent(const Event & event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<ChangeToFullscreenEvent>(OnChangeToFullscreen());
        dispatcher.Dispatch<ChangeToWindowedEvent>(OnChangeToWindowed());
        dispatcher.Dispatch<ResolutionChangeEvent>(OnResolutionChange());
    }

    void RenderTargetLayer::Attach()
    {
        LOG_TRACE("Attaching RenderTargetLayer");

        glGenFramebuffers(1, &m_WindowedRenderTargetID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_WindowedRenderTargetID);

        glGenTextures(1, &m_RenderedTextureID);
        glBindTexture(GL_TEXTURE_2D, m_RenderedTextureID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Window.ResolutionWidth(), m_Window.ResolutionHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderedTextureID, 0);

        glGenRenderbuffers(1, &m_RenderBufferID);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Window.ResolutionWidth(), m_Window.ResolutionHeight());
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
    }

    void RenderTargetLayer::Detach()
    {
        LOG_TRACE("Detaching RenderTargetLayer");

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindTexture(GL_TEXTURE_2D, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glDeleteFramebuffers(1, &m_WindowedRenderTargetID);
    }

    void RenderTargetLayer::HandleAspectRatioChange()
    {
        ImGui::Begin("Scene");

        const auto sceneDimensions = ImGui::GetWindowSize();
        const auto newAspectRatio = sceneDimensions.x / sceneDimensions.y;
        if (!AreSame(m_AspectRatio, newAspectRatio, 0.001f))
        {
            m_AspectRatio = newAspectRatio;
            FireEvent(AspectRatioChangeEvent(newAspectRatio));
        }

        ImGui::End();
    }

    EventHandler<ChangeToFullscreenEvent> RenderTargetLayer::OnChangeToFullscreen()
    {
        return [this](const ChangeToFullscreenEvent& event)
        {
            FireEvent(RenderTargetChangeEvent(m_FullscreenRenderTargetID));
        };
    }

    EventHandler<ChangeToWindowedEvent> RenderTargetLayer::OnChangeToWindowed()
    {
        return [this](const ChangeToWindowedEvent& event)
        {
            FireEvent(RenderTargetChangeEvent(m_WindowedRenderTargetID));
        };
    }

    EventHandler<ResolutionChangeEvent> RenderTargetLayer::OnResolutionChange()
    {
        return [this](const ResolutionChangeEvent& event)
        {
            Detach();
            Attach();
            FireEvent(RenderTargetChangeEvent(m_WindowedRenderTargetID));
        };
    }

}
