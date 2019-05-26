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

        std::vector<unsigned int> MakeIndexesForPointDrawMode(unsigned int numSides) const;
        std::vector<unsigned int> MakeIndexesForLineDrawMode(unsigned int numSides) const;

    private:
        std::vector<Vertex1> MakeVertexes(unsigned int numSides) const;
        std::vector<unsigned int> MakeIndexesForTriangleDrawMode(unsigned int numSides) const;
    };

}
