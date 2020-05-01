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

TEST_CASE("removeVertex","[remove]")
{
    //TODO test iteratorów 
    Graph<int,std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    REQUIRE(g.nrOfVertices() == 6);
    g.insertEdge(1,2,"jeden_dwa");
    g.insertEdge(3,1,"trzy_jeden");
    g.insertEdge(5,0,"piec_zero");
    g.insertEdge(1,1,"jeden_jeden");
    g.removeVertex(0);
    REQUIRE(g.nrOfVertices() == 5);
    REQUIRE(g.nrOfEdges() == 3);
    g.removeVertex(0);
    REQUIRE(g.nrOfVertices() == 4);
    REQUIRE(g.nrOfEdges() == 0);
    g.removeVertex(0);
    REQUIRE(g.nrOfVertices() == 3);
    REQUIRE(g.nrOfEdges() == 0);
}