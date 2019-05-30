#pragma once

#include "types/Vertex1.h"

#include <vector>

namespace graphics {

    class Model
    {
    public:
        Model(std::vector<Vertex1> vertexes, std::vector<unsigned int> indexes)
            : Vertexes(vertexes)
            , Indexes(indexes)
        {}

        virtual ~Model() {};

        unsigned int VertexDataByteSize() const
        {
            return static_cast<unsigned int>(std::size(Vertexes)) * Vertex1::VertexByteSize;
        }

        unsigned int IndexDataByteSize() const
        {
            return static_cast<unsigned int>(std::size(Indexes)) * sizeof(unsigned int);
        }

        unsigned int NumIndexes() const
        {
            return static_cast<unsigned int>(std::size(Indexes));
        }

        std::vector<Vertex1> Vertexes;
        std::vector<unsigned int> Indexes;
    };

}
