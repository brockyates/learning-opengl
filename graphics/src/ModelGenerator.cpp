#include "pch.h"
#include "ModelGenerator.h"

namespace Graphics {

    std::unique_ptr<Model> ModelGenerator::MakeTriangle()
    {
        return std::make_unique<Triangle>();
    }

    std::unique_ptr<Model> ModelGenerator::MakeCircle(unsigned int numSides)
    {
        return std::make_unique<Circle>(numSides);
    }

}
