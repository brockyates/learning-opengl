#pragma once

#include "Model.h"

#include <vector>

namespace Graphics {

    struct Circle : public Model
    {
    public:
        Circle(unsigned int numVertexes = 4);

        [[nodiscard]] std::vector<unsigned int> MakeIndexesForLineDrawMode(unsigned int numVertexes) const;

    private:
        [[nodiscard]] std::vector<Vertex1> MakeVertexes(unsigned int numVertexes) const;
        [[nodiscard]] std::vector<unsigned int> MakeIndexesForTriangleDrawMode(unsigned int numVertexes) const;
    };

}
