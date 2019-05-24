#pragma once

#include "types/Vertex1.h"

#include <vector>

namespace Graphics {

    class Model
    {
    public:
        Model(std::vector<Vertex1> vertexes)
            : Vertexes(vertexes)
        {}

        virtual ~Model() {};

        std::vector<Vertex1> Vertexes;
    };

}
