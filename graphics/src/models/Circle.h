#pragma once

#include "Model.h"

#include <vector>

namespace Graphics
{
    struct Circle final : Model
    {
        explicit Circle(int vertexCount = 4);

        [[nodiscard]] static std::vector<int> MakeIndexesForLineDrawMode(int vertexCount);

    private:
        [[nodiscard]] std::vector<Vertex1> MakeVertexes(int vertexCount) const;
        [[nodiscard]] static std::vector<int> MakeIndexesForTriangleDrawMode(int vertexCount);
    };
}
