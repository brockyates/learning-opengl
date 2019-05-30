#include "pch.h"
#include "ModelGenerator.h"

namespace graphics {

    std::unique_ptr<Model> ModelGenerator::MakeTriangle()
    {
        return std::make_unique<Triangle>();
    }

    std::unique_ptr<Model> ModelGenerator::MakeCircle(unsigned int numVertexes)
    {
        return std::make_unique<Circle>(numVertexes);
    }

}
