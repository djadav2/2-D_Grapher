//
// Created by Dharmil Jadav on 5/4/21.
//

#include <catch2/catch.hpp>
#include <graph.h>

using graph::Function;
using graph::Graph;

TEST_CASE("Invalid constructor declaration") {
  SECTION("Empty vector passed in") {
    std::vector<Function*> functions;
    REQUIRE_THROWS_AS(Graph(functions, 20, 1000), std::invalid_argument);
  }
}