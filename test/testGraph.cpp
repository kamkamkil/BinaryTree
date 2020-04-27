#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_CONSOLE_WIDTH 300
#include "../lib/catch/catch.hpp"
#include "../src/graph.hpp"
#include <string>

TEST_CASE("basic_operation")
{
    Graph<int,std::string> g;
    g.insertVertex(2);
}