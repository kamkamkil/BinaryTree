#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_CONSOLE_WIDTH 300
#include "../lib/catch/catch.hpp"
#include "../src/graph.hpp"
#include <string>

TEST_CASE("basic_operation")
{
    Graph<int, std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    g.insertEdge(1, 2, "a");
    g.insertEdge(2, 1, "b");
    g.insertEdge(3, 5, "qq");
}
TEST_CASE("VerticesIterator", "[iterator]")
{
}
TEST_CASE("EdgesIterator", "[iterator]")
{
}
TEST_CASE("insertVertex")
{
    SECTION("int_vertex")
    {
        Graph<int, std::string> g;
        REQUIRE(*(g.insertVertex(1)) == 1);
        REQUIRE(*(g.insertVertex(1)) == 1);
        REQUIRE(*(g.insertVertex(2)) == 2);
        REQUIRE(*(g.insertVertex(3)) == 3);
        REQUIRE(g.nrOfVertices() == 4);
        REQUIRE(g.vertexData(0) == 1);
        REQUIRE(g.vertexData(1) == 1);
        REQUIRE(g.vertexData(2) == 2);
        REQUIRE(g.vertexData(3) == 3);
    }
    SECTION("string_vertex")
    {
        Graph<std::string, std::string> g;
        REQUIRE(*(g.insertVertex("jeden")) == "jeden");
        REQUIRE(*(g.insertVertex("jeden")) == "jeden");
        REQUIRE(*(g.insertVertex("dwa")) == "dwa");
        REQUIRE(*(g.insertVertex("trzy")) == "trzy");
        REQUIRE(g.nrOfVertices() == 4);
        REQUIRE(g.vertexData(0) == "jeden");
        REQUIRE(g.vertexData(1) == "jeden");
        REQUIRE(g.vertexData(2) == "dwa");
    }
}
TEST_CASE("insertEdge")
{
    Graph<int, std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    // REQUIRE(g.nrOfVertices() == 5);

    auto pair = g.insertEdge(1, 2, "jeden_dwa");
    // REQUIRE(*(pair.first) == "jeden_dwa");
    REQUIRE(pair.second);
    pair = g.insertEdge(3, 4, "trzy_cztery");
    // REQUIRE(*pair.first == "trzy_cztery");
    REQUIRE(pair.second);
    pair = g.insertEdge(2, 1, "dwa_jeden");
    // REQUIRE(*pair.first == "dwa_jeden");
    REQUIRE(pair.second);
    pair = g.insertEdge(1, 2, "jeden_dwa_zmieniony");
    // REQUIRE(*pair.first == "jeden_dwa_zmieniony");
    REQUIRE(pair.second);
    pair = g.insertEdge(1, 2, "jeden_dwa_nowy", false);
    // REQUIRE(*pair.first == "jeden_dwa_zmieniony");
    REQUIRE_FALSE(pair.second);
    // pair = g.insertEdge(5,5, "nie_powinno_sie_udac"); // TODO dodac wyjatek albo cos
    // REQUIRE(pair.first == g.endEdges());
    REQUIRE_FALSE(pair.second);
    REQUIRE(g.edgeExist(1, 2));
    REQUIRE(g.edgeExist(3, 4));
    REQUIRE_FALSE(g.edgeExist(4, 4));
    REQUIRE_FALSE(g.edgeExist(5, 5));
    REQUIRE(g.edgeLabel(3, 4) == "trzy_cztery");
    REQUIRE(g.edgeLabel(1, 2) == "jeden_dwa_zmieniony");
    REQUIRE(g.nrOfEdges() == 3);
}

TEST_CASE("removeVertex", "[remove]")
{
    Graph<int, std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    REQUIRE(g.nrOfVertices() == 6);
    g.insertEdge(1, 2, "jeden_dwa");
    g.insertEdge(3, 1, "trzy_jeden");
    g.insertEdge(5, 0, "piec_zero");
    g.insertEdge(1, 1, "jeden_jeden");
    REQUIRE(*g.removeVertex(0) == 2);
    REQUIRE(g.nrOfVertices() == 5);
    REQUIRE(g.nrOfEdges() == 3);
    REQUIRE(*g.removeVertex(1) == 4);
    REQUIRE(g.nrOfVertices() == 4);
    REQUIRE(g.nrOfEdges() == 2);
    g.removeVertex(3);
    REQUIRE(g.nrOfVertices() == 3);
    REQUIRE(g.nrOfEdges() == 2);
}
TEST_CASE("removeEdge", "[remove]")
{
    Graph<int, std::string> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    REQUIRE(g.nrOfVertices() == 6);
    g.insertEdge(1, 2, "jeden_dwa");
    g.insertEdge(3, 1, "trzy_jeden");
    g.insertEdge(5, 0, "piec_zero");
    g.insertEdge(2, 2, "dwa_dwa");
    g.insertEdge(3, 2, "trzy_dwa");
    g.insertEdge(0, 0, "zero_zero");
    g.removeEdge(0,0);
    REQUIRE_FALSE(g.edgeExist(0,0));
    g.removeEdge(3,2);
    g.removeEdge(1,2);
    REQUIRE_FALSE(g.edgeExist(3,2));
    REQUIRE_FALSE(g.edgeExist(1,2));
}