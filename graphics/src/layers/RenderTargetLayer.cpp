#include "pch.h"
#include "RenderTargetLayer.h"

#include "events/EventDispatcher.h"
#include "events/RenderTargetChangeEvent.h"

#include "logging/Log.h"

#include "helpers/MathHelpers.h"

#include "renderer/Renderer.h"

#include "window/Window.h"

#include <glad/glad.h>
#include <imgui.h>

#include <sstream>
#include <utility>

namespace Graphics {

    RenderTargetLayer::RenderTargetLayer(const Window& window, EventHandler<Event> eventCallback)
        : Layer(window, std::move(eventCallback), "Render to Texture")
        , aspectRatio_(window.AspectRatio())
    {
        Attach();
        Layer::FireEvent(RenderTargetChangeEvent(windowedRenderTarget_));
    }

    RenderTargetLayer::~RenderTargetLayer()
    {
        //Todo: delete texture
        Renderer::DeleteRenderBuffer(renderBuffer_);
        Detach();
    }

    void RenderTargetLayer::RenderUi()
    {
        HandleAspectRatioChange();

        ImGui::Begin("Scene");
        const auto scenePosition = ImGui::GetCursorScreenPos();
        const auto sceneSize = ImGui::GetContentRegionAvail();

        ImGui::GetWindowDrawList()->AddImage(
            reinterpret_cast<void *>(static_cast<intptr_t>(renderedTextureId_)),
            ImVec2(scenePosition),
            ImVec2(scenePosition.x + sceneSize.x, scenePosition.y + sceneSize.y),
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
        LogTrace("Attaching RenderTargetLayer");

        windowedRenderTarget_ = Renderer::GenFrameBuffer();
        Renderer::BindFrameBuffer(windowedRenderTarget_);

        glGenTextures(1, &renderedTextureId_);
        glBindTexture(GL_TEXTURE_2D, renderedTextureId_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window_.ResolutionWidth(), window_.ResolutionHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderedTextureId_, 0);

        renderBuffer_ = Renderer::GenRenderBuffer();
        Renderer::BindRenderBuffer(renderBuffer_);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window_.ResolutionWidth(), window_.ResolutionHeight());
        Renderer::UnbindRenderBuffer();

        Renderer::SetFrameBufferRenderBuffer(renderBuffer_);

        const auto frameBufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (!(frameBufferStatus == GL_FRAMEBUFFER_COMPLETE))
        {
            LogGlError([&]() {
                std::stringstream ss;
                ss << "Frame buffer status error. Status: " << std::hex << frameBufferStatus;
                return ss.str();
            }());
        }
        else
        {
            LogGlTrace("Frame buffer complete");
        }

        Renderer::UnbindFrameBuffer();
    }

    void RenderTargetLayer::Detach()
    {
        LogTrace("Detaching RenderTargetLayer");

        glBindTexture(GL_TEXTURE_2D, 0);
        Renderer::UnbindAll();

        Renderer::DeleteFrameBuffer(windowedRenderTarget_);
    }

    void RenderTargetLayer::HandleAspectRatioChange()
    {
        ImGui::Begin("Scene");

        const auto sceneDimensions = ImGui::GetWindowSize();
        const auto newAspectRatio = sceneDimensions.x / sceneDimensions.y;
        if (!AreSame(aspectRatio_, newAspectRatio, 0.001f))
        {
            aspectRatio_ = newAspectRatio;
            FireEvent(AspectRatioChangeEvent(newAspectRatio));
        }

        ImGui::End();
    }

    EventHandler<ChangeToFullscreenEvent> RenderTargetLayer::OnChangeToFullscreen()
    {
        return [this](const ChangeToFullscreenEvent&)
        {
            FireEvent(RenderTargetChangeEvent(fullscreenRenderTarget_));
        };
    }

    EventHandler<ChangeToWindowedEvent> RenderTargetLayer::OnChangeToWindowed()
    {
        return [this](const ChangeToWindowedEvent&)
        {
            FireEvent(RenderTargetChangeEvent(windowedRenderTarget_));
        };
    }

    EventHandler<ResolutionChangeEvent> RenderTargetLayer::OnResolutionChange()
    {
        return [this](const ResolutionChangeEvent&)
        {
            Detach();
            Attach();
            FireEvent(RenderTargetChangeEvent(windowedRenderTarget_));
        };
    }

}
