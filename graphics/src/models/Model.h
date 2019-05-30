#pragma once

#include "types/Vertex1.h"

#include <utility>
#include <vector>

namespace Graphics {

    class Model
    {
    public:
        Model(std::vector<Vertex1> vertexes, std::vector<unsigned int> indexes)
            : Vertexes(std::move(vertexes))
            , Indexes(std::move(indexes))
        {}

        virtual ~Model() {};

        [[nodiscard]] unsigned int VertexDataByteSize() const
        {
            return static_cast<unsigned int>(std::size(Vertexes)) * Vertex1::VertexByteSize;
        }

        [[nodiscard]] unsigned int IndexDataByteSize() const
        {
            return static_cast<unsigned int>(std::size(Indexes)) * sizeof(unsigned int);
        }

        [[nodiscard]] unsigned int NumIndexes() const
        {
            return static_cast<unsigned int>(std::size(Indexes));
        }

        std::vector<Vertex1> Vertexes;
        std::vector<unsigned int> Indexes;
    };

}
