#include "pch.h"

#include "models/Circle.h"
#include "models/Triangle.h"

#include "ModelGenerator.h"

namespace Graphics
{
    std::unique_ptr<Model> ModelGenerator::MakeTriangle()
    {
        return std::make_unique<Triangle>();
    }

    std::unique_ptr<Model> ModelGenerator::MakeCircle(int vertexCount)
    {
        return std::make_unique<Circle>(vertexCount);
    }
}
