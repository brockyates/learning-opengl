#pragma once

#include "events/EventSystem.h"
#include "layers/Layer.h"
#include "ModelGenerator.h"
#include "models/Model.h"
#include "types/Vertex1.h"
#include "Window.h"

#include <glm/glm.hpp>

namespace Graphics {

    struct WindowProperties;

    class CircleDemo : public Layer
    {
    public:
        CircleDemo(const Window& window, EventHandler<Event> eventCallback);

        virtual void RenderScene() override;
        virtual void RenderUI() override;

        virtual void Attach() override;
        virtual void Detach() override;
        virtual bool IsAttached() const override { return m_Attached; }

        virtual std::string PopupText() const override;
        virtual std::string Description() const override;

        virtual void OnEvent(const Event& event) override;

    private:
        //Event handlers
        EventHandler<RenderTargetChangedEvent> OnRenderTargetChanged();

    private:
        bool m_Attached = false;

        //OpenGL state
        unsigned int m_FrameBufferID = 0;
        unsigned int m_ShaderID = 0;
        unsigned int m_VertexArrayID = 0;
        unsigned int m_IndexBufferID = 0;
        unsigned int m_VertexBufferID = 0;
        unsigned int m_PointsizeUniformLocation = 0;

        //Buffer data
        std::unique_ptr<Model> m_CircleModel = ModelGenerator::MakeCircle();
    };

}
