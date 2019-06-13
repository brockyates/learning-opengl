#pragma once

#include "types/Vertex1.h"

#include <utility>
#include <vector>

namespace Graphics
{
    class Model
    {
    public:
        Model(std::vector<Vertex1> vertexes, std::vector<int> indexes)
            : Vertexes(std::move(vertexes))
            , Indexes(std::move(indexes))
        {}

        virtual ~Model() = default;

        Model(const Model&) = default;
        Model(Model&&) = default;

        Model& operator=(const Model&) = default;
        Model& operator=(Model&&) = default;

        [[nodiscard]] size_t VertexDataByteSize() const
        {
            return std::size(Vertexes) * Vertex1::VERTEX_BYTE_SIZE;
        }

        [[nodiscard]] size_t IndexDataByteSize() const
        {
            return std::size(Indexes) * sizeof(int);
        }

        [[nodiscard]] int IndexCount() const
        {
            return static_cast<int>(std::size(Indexes));
        }

        std::vector<Vertex1> Vertexes;
        std::vector<int> Indexes;
    };
}
