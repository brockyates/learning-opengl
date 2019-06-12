#pragma once

#include "models/Model.h"

#include <memory>

namespace Graphics
{
    class ModelGenerator
    {
    public:
        static std::unique_ptr<Model> MakeTriangle();
        static std::unique_ptr<Model> MakeCircle(unsigned int numVertexes);
    };
}
