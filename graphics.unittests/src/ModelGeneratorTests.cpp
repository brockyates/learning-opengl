#include "pch.h"
#include "catch.hpp"

#include "models/ModelGenerator.h"

using namespace Graphics;

TEST_CASE("ModelGenerator sanity test", "[ModelGenerator]")
{
    const auto model = ModelGenerator::MakeTriangle();

    REQUIRE(!std::empty(model->Vertexes));
}
