#pragma once

#include "Model.h"

#include <vector>

namespace Graphics {

    struct Circle : public Model
    {
    public:
        Circle(unsigned int numVertexes = 4);

        std::vector<unsigned int> MakeIndexesForLineDrawMode(unsigned int numVertexes) const;

    private:
        std::vector<Vertex1> MakeVertexes(unsigned int numVertexes) const;
        std::vector<unsigned int> MakeIndexesForTriangleDrawMode(unsigned int numVertexes) const;
    };

}
