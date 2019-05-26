#pragma once

#include "models/Model.h"
#include "models/Triangle.h"
#include "models/Circle.h"

#include <memory>

namespace Graphics {

    class ModelGenerator
    {
    public:
        static std::unique_ptr<Model> MakeTriangle() { return std::make_unique<Triangle>(); }
        static std::unique_ptr<Model> MakeCircle() { return std::make_unique<Circle>(); }
    };

}
