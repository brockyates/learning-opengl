#include "pch.h"
#include "BaseLayer.h"
#include "renderer/Shader.h"

#include <glad/glad.h>

namespace Graphics {

    void BaseLayer::OnRender()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.7f, 1.0f);
    }

}
