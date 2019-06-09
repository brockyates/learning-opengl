#pragma once

#include "detail/Uint32Id.h"

namespace Graphics {

    using ShaderProgram = Detail::Uint32Id<Detail::ShaderProgramTag>;
    using VertexShader = Detail::Uint32Id<Detail::VertexShaderTag>;
    using FragmentShader = Detail::Uint32Id<Detail::FragmentShaderTag>;

}