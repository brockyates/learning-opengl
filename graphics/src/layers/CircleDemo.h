#pragma once

#include "events/EventSystem.h"
#include "layers/Layer.h"
#include "ModelGenerator.h"
#include "models/Model.h"
#include "Timer.h"
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
        //Scene rendering
        void UpdateTiming();
        void UpdateSides();
        void AnimateSides();

    private:
        bool m_Attached = false;
        double m_LastTime = Timer::Get();
        double m_DeltaTime = 0.0;
        double m_TimeSinceLastChange = 0.0;
        float m_AnimationInterval = 0.5;
        bool m_SidesIncreasing = true;
        unsigned int m_MaxSides = 50;

        //OpenGL state
        unsigned int m_FrameBufferID = 0;
        unsigned int m_ShaderID = 0;
        unsigned int m_VertexArrayID = 0;
        unsigned int m_IndexBufferID = 0;
        unsigned int m_VertexBufferID = 0;
        unsigned int m_PointsizeUniformLocation = 0;

        //Buffer data
        unsigned int m_Sides = 3;
        unsigned int m_NextSides = 3;
        std::unique_ptr<Model> m_CircleModel = ModelGenerator::MakeCircle(m_Sides);
    };

}
