#pragma once

#include "types/Vertex1.h"

#include <vector>

namespace Graphics {

    class Model
    {
    public:
        Model(std::vector<Vertex1> vertexes, std::vector<unsigned int> indexes)
            : Vertexes(vertexes)
            , Indexes(indexes)
        {}

        virtual ~Model() {};

        std::vector<Vertex1> Vertexes;
        std::vector<unsigned int> Indexes;
    };

}
