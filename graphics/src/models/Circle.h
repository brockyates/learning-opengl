#pragma once

#include "Model.h"

#include <vector>

namespace Graphics
{
    struct Circle final : Model
    {
        explicit Circle(uint32_t numVertexes = 4);

        [[nodiscard]] static std::vector<int> MakeIndexesForLineDrawMode(uint32_t numVertexes);

    private:
        [[nodiscard]] std::vector<Vertex1> MakeVertexes(uint32_t numVertexes) const;
        [[nodiscard]] static std::vector<int> MakeIndexesForTriangleDrawMode(uint32_t numVertexes);
    };
}
