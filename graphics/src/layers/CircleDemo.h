#pragma once

#include "events/EventSystem.h"
#include "layers/Layer.h"
#include "ModelGenerator.h"
#include "models/Circle.h"
#include "Timer.h"
#include "types/Vertex1.h"
#include "Window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
        EventHandler<RenderTargetChangedEvent> OnRenderTargetChange();
        EventHandler<AspectRatioChangeEvent> OnAspectRatioChange();

    private:
        //Scene rendering
        void UpdateTiming();
        void UpdateSides();
        void AnimateSides();

    private:
        unsigned int m_MaxSides = 50;
        unsigned int m_Sides = m_MaxSides;
        unsigned int m_NextSides = m_MaxSides;
        std::unique_ptr<Circle> m_CircleModel = std::make_unique<Circle>(m_Sides);

        bool m_Attached = false;
        double m_LastTime = Timer::Get();
        double m_DeltaTime = 0.0;
        double m_TimeSinceLastChange = 0.0;
        float m_AnimationInterval = 0.5;
        bool m_SidesIncreasing = false;
        bool m_AnimationEnabled = false;

        //OpenGL state
        unsigned int m_FrameBufferID = 0;

        unsigned int m_TriangleShaderID = 0;
        unsigned int m_LineShaderID = 0;

        unsigned int m_VertexArrayID = 0;
        unsigned int m_VertexBufferID = 0;

        unsigned int m_LineColorUniformLocation = 0;
        unsigned int m_ProjMatrixUniformLocation = 0;

        unsigned int m_TriangleIndexBufferID = 0;
        unsigned int m_LineIndexBufferID = 0;

        unsigned int m_NumLineIndexes = 0;

        float m_Aspect = 1.0f;
        glm::mat4 m_ProjectionMatrix = glm::ortho(-1.0f * m_Window.AspectRatio(), 1.0f * m_Window.AspectRatio(), -1.0f, 1.0f);
    };

}
