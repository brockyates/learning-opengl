#pragma once

#include "Model.h"
#include "types/Vertex1.h"

#include <glm/glm.hpp>

#include <vector>

namespace Graphics {

    struct Circle : public Model
    {
    public:
        Circle(unsigned int numSides = 3);

    private:
        std::vector<Vertex1> MakeVertexes(unsigned int numSides) const;
        std::vector<unsigned int> MakeIndexesForTriangleDrawMode(unsigned int numSides) const;
    };

}
