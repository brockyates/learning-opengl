#include "pch.h"
#include "catch.hpp"

unsigned int FACTORIAL(const unsigned int number) {
    return number <= 1 ? number : FACTORIAL(number - 1)*number;
}

TEST_CASE("Factorials are computed", "[factorial]") {
    REQUIRE(FACTORIAL(1) == 1);
    REQUIRE(FACTORIAL(2) == 2);
    REQUIRE(FACTORIAL(3) == 6);
    REQUIRE(FACTORIAL(10) == 3628800);
}
