#pragma once

#include "types/Vertex1.h"

#include <utility>
#include <vector>

namespace Graphics
{
    class Model
    {
    public:
        Model(std::vector<Vertex1> vertexes, std::vector<uint32_t> indexes)
            : Vertexes(std::move(vertexes))
            , Indexes(std::move(indexes))
        {}

        virtual ~Model() = default;

        Model(const Model&) = default;
        Model(Model&&) = default;

        Model& operator=(const Model&) = default;
        Model& operator=(Model&&) = default;

        [[nodiscard]] uint32_t VertexDataByteSize() const
        {
            return static_cast<uint32_t>(std::size(Vertexes)) * Vertex1::VERTEX_BYTE_SIZE;
        }

        [[nodiscard]] uint32_t IndexDataByteSize() const
        {
            return static_cast<uint32_t>(std::size(Indexes)) * sizeof(uint32_t);
        }

        [[nodiscard]] uint32_t NumIndexes() const
        {
            return static_cast<uint32_t>(std::size(Indexes));
        }

        std::vector<Vertex1> Vertexes;
        std::vector<uint32_t> Indexes;
    };
}
