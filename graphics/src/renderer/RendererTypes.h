#pragma once

#include "detail/Uint32Id.h"

namespace Graphics {

#ifdef OPENGL_RENDERER
    class OpenGlRenderer;
    using Renderer = OpenGlRenderer;
#else
    class TestRenderer;
    using Renderer = TestRenderer;
#endif //OPENGL_RENDERER

    using Program = Detail::Uint32Id<Detail::ProgramTag>;

}
