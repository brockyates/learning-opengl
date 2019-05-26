#pragma once

#include "Model.h"
#include "types/Vertex1.h"

#include <glm/glm.hpp>

#include <vector>

namespace Graphics {

    struct Circle : public Model
    {
    public:
        Circle();

    private:
        std::vector<Vertex1> MakeVertexes() const;
        std::vector<unsigned int> MakeIndexes() const;
    };

}
