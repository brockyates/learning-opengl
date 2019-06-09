#pragma once

#include "detail/Uint32Id.h"

namespace Graphics {

    using FragmentShader = Detail::Uint32Id<Detail::FragmentShaderTag>;
    using FrameBuffer = Detail::Uint32Id<Detail::FrameBufferTag>;
    using ShaderProgram = Detail::Uint32Id<Detail::ShaderProgramTag>;
    using VertexShader = Detail::Uint32Id<Detail::VertexShaderTag>;

}