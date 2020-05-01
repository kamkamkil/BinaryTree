#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_CONSOLE_WIDTH 300
#include "../lib/catch/catch.hpp"
#include "../src/graph.hpp"
#include <string>

TEST_CASE("basic_operation")
{
    Graph<int,std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    g.insertEdge(1,2,"a");
    g.insertEdge(2,1,"b");
    g.insertEdge(3,5,"qq");
}