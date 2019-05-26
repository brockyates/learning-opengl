#include "pch.h"
#include "Circle.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Graphics {

    Circle::Circle(unsigned int numSides)
        : Model(MakeVertexes(numSides), MakeIndexesForTriangleDrawMode(numSides))
    {}

    std::vector<Vertex1> Circle::MakeVertexes(unsigned int numSides) const
    {
        const auto defaultColor = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
        const auto origin = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };
        const auto basePoint = glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f };
        const auto angle = 2.0f * glm::pi<float>() / static_cast<float>(numSides);

        std::vector<Vertex1> vertexes;
        vertexes.reserve(numSides);

        vertexes.emplace_back(origin, defaultColor);
        vertexes.emplace_back(basePoint, defaultColor);

        glm::vec3 rotationAxis(0.0f, 0.0f, 1.0f);

        for (auto i = 1u; i < numSides; i++) //Note the loop index starts at 1.
        {
            glm::mat4 transform = glm::rotate(glm::mat4(1.0f), i*angle, rotationAxis);
            glm::vec4 newPoint = transform * basePoint;

            vertexes.emplace_back(newPoint, defaultColor);
        }

        return vertexes;
    }

    std::vector<unsigned int> Circle::MakeIndexesForTriangleDrawMode(unsigned int numSides) const
    {
        std::vector<unsigned int> indexes;
        indexes.reserve(3 * numSides);

        for (auto i = 0u; i < numSides - 1; i++)
        {
            indexes.emplace_back(i + 2);
            indexes.emplace_back(0);
            indexes.emplace_back(i + 1);
        };

        indexes.emplace_back(1);
        indexes.emplace_back(0);
        indexes.emplace_back(numSides);

        return indexes;
    }

    std::vector<unsigned int> Circle::MakeIndexesForPointDrawMode(unsigned int numSides) const
    {
        std::vector<unsigned int> indexes;
        indexes.reserve(numSides + 1);

        for (auto i = 0u; i < numSides + 1; i++)
        {
            indexes.emplace_back(i);
        }

        return indexes;
    }

    std::vector<unsigned int> Circle::MakeIndexesForLineDrawMode(unsigned int numSides) const
    {
        std::vector<unsigned int> indexes;
        indexes.reserve(numSides * 4);

        for (auto i = 0u; i < numSides - 1; i++)
        {
            indexes.emplace_back(0);
            indexes.emplace_back(i+1);
            indexes.emplace_back(i+1);
            indexes.emplace_back(i+2);
        }

        indexes.emplace_back(0);
        indexes.emplace_back(numSides);
        indexes.emplace_back(numSides);
        indexes.emplace_back(1);

        return indexes;
    }

}
