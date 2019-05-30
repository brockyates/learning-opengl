#include "pch.h"
#include "Circle.h"

#include "types/Vertex1.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Graphics {

    Circle::Circle(unsigned int numVertexes)
        : Model(MakeVertexes(numVertexes), MakeIndexesForTriangleDrawMode(numVertexes))
    {}

    std::vector<Vertex1> Circle::MakeVertexes(unsigned int numVertexes) const
    {
        const auto defaultColor = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
        const auto origin = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };
        const auto basePoint = glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f };
        const auto angle = 2.0f * glm::pi<float>() / static_cast<float>(numVertexes - 1);

        std::vector<Vertex1> vertexes;
        vertexes.reserve(numVertexes);
        vertexes.emplace_back(origin, defaultColor);
        vertexes.emplace_back(basePoint, defaultColor);

        glm::vec3 rotationAxis(0.0f, 0.0f, 1.0f);

        for (auto i = 1u; i < numVertexes - 1; i++) //Note the loop index starts at 1.
        {
            glm::mat4 transform = glm::rotate(glm::mat4(1.0f), i*angle, rotationAxis);
            glm::vec4 nextPoint = transform * basePoint;

            vertexes.emplace_back(nextPoint, defaultColor);
        }

        return vertexes;
    }

    std::vector<unsigned int> Circle::MakeIndexesForTriangleDrawMode(unsigned int numVertexes) const
    {
        std::vector<unsigned int> indexes;
        indexes.reserve(3 * (numVertexes - 1));

        for (auto i = 0u; i < (numVertexes - 2); i++)
        {
            indexes.emplace_back(i+2);
            indexes.emplace_back(0);
            indexes.emplace_back(i+1);
        };

        indexes.emplace_back(1);
        indexes.emplace_back(0);
        indexes.emplace_back(numVertexes - 1);

        return indexes;
    }

    std::vector<unsigned int> Circle::MakeIndexesForLineDrawMode(unsigned int numVertexes) const
    {
        std::vector<unsigned int> indexes;
        indexes.reserve((numVertexes - 1) * 4);

        for (auto i = 0u; i < numVertexes - 2; i++)
        {
            indexes.emplace_back(0);
            indexes.emplace_back(i+1);
            indexes.emplace_back(i+1);
            indexes.emplace_back(i+2);
        }

        indexes.emplace_back(0);
        indexes.emplace_back(numVertexes - 1);
        indexes.emplace_back(numVertexes - 1);
        indexes.emplace_back(1);

        return indexes;
    }

}
