#pragma once

#include "Model.h"

#include <vector>

namespace Graphics {

    struct Circle final : Model
    {
        explicit Circle(unsigned int numVertexes = 4);

        [[nodiscard]] static std::vector<unsigned int> MakeIndexesForLineDrawMode(unsigned int numVertexes);

    private:
        [[nodiscard]] std::vector<Vertex1> MakeVertexes(unsigned int numVertexes) const;
        [[nodiscard]] static std::vector<unsigned int> MakeIndexesForTriangleDrawMode(unsigned int numVertexes);
    };

}
