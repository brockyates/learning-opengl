#include "pch.h"
#include "Circle.h"

#include "helpers/GlobalMacros.h"

#include "types/Vertex1.h"

#include <glm/gtc/matrix_transform.hpp>

#include <sstream>

namespace
{
    int ValidateVertexCount(const int vertexCount)
    {
        if(vertexCount < 4)
        {
            std::stringstream ss;
            ss << "Attempted to generate circle model with " << vertexCount << " vertexes. Minimum number of vertexes for this model is 4.";
            AppAssert(vertexCount > 3, ss.str());
        }

        return vertexCount;
    }
}

namespace Graphics
{
    Circle::Circle(const int vertexCount)
        : Model(MakeVertexes(ValidateVertexCount(vertexCount)), MakeIndexesForTriangleDrawMode(vertexCount))
    {}

    std::vector<Vertex1> Circle::MakeVertexes(const int vertexCount) const
    {
        const auto defaultColor = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };
        const auto origin = glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f };
        const auto basePoint = glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f };
        const auto angle = 2.0f * glm::pi<float>() / static_cast<float>(vertexCount - 1);

        std::vector<Vertex1> vertexes;
        vertexes.reserve(vertexCount);
        vertexes.emplace_back(origin, defaultColor);
        vertexes.emplace_back(basePoint, defaultColor);

        const glm::vec3 rotationAxis(0.0f, 0.0f, 1.0f);

        for (auto i = 1; i < vertexCount - 1; i++) //Note the loop index starts at 1.
        {
            const auto transform = rotate(glm::mat4(1.0f), i*angle, rotationAxis);
            const auto nextPoint = transform * basePoint;

            vertexes.emplace_back(nextPoint, defaultColor);
        }

        return vertexes;
    }

    std::vector<int> Circle::MakeIndexesForTriangleDrawMode(const int vertexCount)
    {
        std::vector<int> indexes;
        indexes.reserve(3 * (vertexCount - 1));

        for (auto i = 0; i < vertexCount - 2; i++)
        {
            indexes.emplace_back(i+2);
            indexes.emplace_back(0);
            indexes.emplace_back(i+1);
        }

        indexes.emplace_back(1);
        indexes.emplace_back(0);
        indexes.emplace_back(vertexCount - 1);

        return indexes;
    }

    std::vector<int> Circle::MakeIndexesForLineDrawMode(const int vertexCount)
    {
        std::vector<int> indexes;
        indexes.reserve((vertexCount - 1) * 4);

        for (auto i = 0; i < vertexCount - 2; i++)
        {
            indexes.emplace_back(0);
            indexes.emplace_back(i+1);
            indexes.emplace_back(i+1);
            indexes.emplace_back(i+2);
        }

        indexes.emplace_back(0);
        indexes.emplace_back(vertexCount - 1);
        indexes.emplace_back(vertexCount - 1);
        indexes.emplace_back(1);

        return indexes;
    }
}
