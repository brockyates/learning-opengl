#pragma once

#include "models/Model.h"
#include "models/Triangle.h"
#include "models/Circle.h"

#include <memory>

namespace graphics {

    class ModelGenerator
    {
    public:
        static std::unique_ptr<Model> MakeTriangle();
        static std::unique_ptr<Model> MakeCircle(unsigned int numVertexes);
    };

}
