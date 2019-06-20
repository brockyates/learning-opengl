#include "pch.h"
#include "catch.hpp"

#include "models/ModelGenerator.h"

using namespace Graphics;

TEST_CASE("ModelGenerator sanity test", "[ModelGenerator]")
{
    const auto model = ModelGenerator::MakeTriangle();

    REQUIRE(!std::empty(model->Vertexes));
}

TEST_CASE("ModelGenerator triangle vertex count", "[ModelGenerator]")
{
    const auto model = ModelGenerator::MakeTriangle();
    const auto expectedVertexCount = 3;

    REQUIRE(std::size(model->Vertexes) == expectedVertexCount);
}

TEST_CASE("ModelGenerator triangle vertex data byte size ", "[ModelGenerator]")
{
    const auto model = ModelGenerator::MakeTriangle();

    // 1 vertex = 4 position floats, 4 color floats = 8 floats * 4 bytes / float = 32 bytes / vertex
    // 32 bytes / vertex * 3 vertexes = 96 bytes
    const auto expectedVertexDataByteSize = 96;

    REQUIRE(model->VertexDataByteSize() == expectedVertexDataByteSize);
}

TEST_CASE("ModelGenerator triangle index count", "[ModelGenerator]")
{
    const auto model = ModelGenerator::MakeTriangle();
    const auto expectedIndexCount = 3;

    REQUIRE(model->IndexCount() == expectedIndexCount);
}

TEST_CASE("ModelGenerator triangle index data byte size ", "[ModelGenerator]")
{
    const auto model = ModelGenerator::MakeTriangle();

    // 3 indexes * 4 bytes per index = 12 bytes
    const auto expectedIndexDataByteSize = 12;

    REQUIRE(model->IndexDataByteSize() == expectedIndexDataByteSize);
}
