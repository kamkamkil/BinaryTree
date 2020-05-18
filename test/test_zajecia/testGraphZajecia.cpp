

#include <iostream>
#include <functional>
#include <cstdint>
#include <string>
#include <cmath>
#include "../src/graph.hpp"
#include "../src/graphAlgorithms.hpp"
// #include "../src/drawgraph.hpp"

using namespace std;

template <typename Iter>
void printDebugInsertInfo(const std::pair<Iter, bool> &insert_info)
{
    if (insert_info.first)
    {
        std::cout << "Dodano " << (insert_info.second ? "(zastepujac) " : "") << *insert_info.first << std::endl;
    }
    else
        std::cout << "Nie dodano" << std::endl;
}

template <typename Iter>
void printDebugRemoveInfo(const Iter &next)
{
    if (next)
        std::cout << "Usunięto, następny element to: " << *next << std::endl;
    else
        std::cout << "Nie usunięto, lub następny element to end()" << std::endl;
}

int main()
{
    Graph<std::string, double> g;
    {
        for (std::size_t i = 0u; i < 6u; ++i)
        {
            g.insertVertex("data " + std::to_string(i));
        }

        for (std::size_t i = 0u; i < g.nrOfVertices(); ++i)
        {
            for (std::size_t j = 0u; j < g.nrOfVertices(); ++j)
            {
                if ((i + j) & 1u || i & 1u)
                {
                    g.insertEdge(i, j, ((i != j) ? (i + j) / 2. : 1.));
                }
            }
        }

        g.printNeighborhoodMatrix();
        std::cout << std::endl;

        printDebugRemoveInfo(g.removeEdge(0, 2));
        printDebugInsertInfo(g.insertEdge(0, 2, 4.));
        printDebugRemoveInfo(g.removeVertex(1));
        printDebugRemoveInfo(g.removeEdge(2, 2));
        printDebugRemoveInfo(g.removeEdge(2, 3));
        printDebugRemoveInfo(g.removeEdge(4, 3));
        printDebugRemoveInfo(g.removeVertex(8));
        std::cout << "Nr of vertices: " << g.nrOfVertices() << std::endl;
        std::cout << "Nr of edges: " << g.nrOfEdges() << std::endl;
        std::cout << std::endl;
        g.printNeighborhoodMatrix();
        std::cout << std::endl;
        std::cout << "Vertices data:" << std::endl;
        for (auto v_it = g.beginVertices(); v_it != g.endVertices(); ++v_it)
        {
            std::cout << *v_it << ", ";
        }
        std::cout << std::endl
                  << std::endl;
        std::cout << "Edges data:" << std::endl;
        for (auto e_it = g.beginEdges(); e_it != g.endEdges(); ++e_it)
        {
            std::cout << *e_it << ", ";
        }
        std::cout << std::endl
                  << std::endl;

        std::cout << "DFS(1):" << std::endl;
        for (auto dfs_it = g.beginDFS(1); dfs_it != g.endDFS(); ++dfs_it)
        {
            std::cout << *dfs_it << ", ";
        }
        std::cout << std::endl
                  << std::endl;
        std::cout << "BFS(1):" << std::endl;
        for (auto bfs_it = g.beginBFS(1); bfs_it != g.endBFS(); ++bfs_it)
        {
            std::cout << *bfs_it << ", ";
        }
        std::cout << std::endl
                  << std::endl;

        std::vector<Graph<std::string, double>> vg, vg2;
        vg.resize(1000);
        for (auto &e : vg)
        {
            e = g;
            e.insertVertex("data x");
        }
        vg2.resize(1000);
        for (std::size_t i = 0u; i < vg.size(); ++i)
        {
            vg2[i] = std::move(vg[i]);
        }
        for (auto &e : vg2)
        {
            e.removeVertex(2);
        }
        vg = vg2;
        vg2.clear();
        vg.front().insertEdge(0, 4);

        g = std::move(vg.front());
    }
    g.printNeighborhoodMatrix();

    std::cout << std::endl;
    std::cout << "Vertices data:" << std::endl;
    for (auto v_it = g.beginVertices(); v_it != g.endVertices(); ++v_it)
    {
        std::cout << *v_it << ", ";
    }
    std::cout << std::endl
              << std::endl;
    std::cout << "Edges data:" << std::endl;
    for (auto e_it = g.beginEdges(); e_it != g.endEdges(); ++e_it)
    {
        std::cout << *e_it << ", ";
    }
    std::cout << std::endl
              << std::endl;

    std::cout << "DFS(1):" << std::endl;
    DFS<std::string, double>(g, 1, [](const std::string &v) -> void { std::cout << v << ", "; });
    //for(auto dfs_it = g.beginDFS(1); dfs_it != g.endDFS(); ++dfs_it) { std::cout << *dfs_it << ", "; }
    std::cout << std::endl;
    std::cout << "BFS(1):" << std::endl;
    BFS<std::string, double>(g, 1, [](const std::string &v) -> void { std::cout << v << ", "; });
    //for(auto dfs_it = g.beginDFS(1); dfs_it != g.endDFS(); ++dfs_it) { std::cout << *dfs_it << ", "; }
    std::cout << std::endl;

    std::cout << "DFS(1):" << std::endl;
    for (auto dfs_it = g.beginDFS(1); dfs_it != g.endDFS(); ++dfs_it)
    {
        std::cout << *dfs_it << ", ";
    }
    std::cout << std::endl;
    std::cout << "BFS(1):" << std::endl;
    for (auto bfs_it = g.beginBFS(1); bfs_it != g.endBFS(); ++bfs_it)
    {
        std::cout << *bfs_it << ", ";
    }
    std::cout << std::endl;

    std::cout << std::endl;
    printDebugInsertInfo(g.insertEdge(1, 2, 2));
    printDebugInsertInfo(g.insertEdge(1, 4, 2));
    printDebugInsertInfo(g.insertEdge(2, 1, 2));
    printDebugInsertInfo(g.insertEdge(2, 4, 2));
    printDebugInsertInfo(g.insertEdge(4, 1, 2));
    printDebugInsertInfo(g.insertEdge(4, 2, 2));
    std::cout << std::endl;
    g.printNeighborhoodMatrix();
    std::cout << std::endl;

    std::cout << "DFS(1):" << std::endl;
    for (auto dfs_it = g.beginDFS(1); dfs_it != g.endDFS(); ++dfs_it)
    {
        std::cout << *dfs_it << ", ";
    }
    std::cout << std::endl;
    std::cout << "BFS(1):" << std::endl;
    for (auto bfs_it = g.beginBFS(1); bfs_it != g.endBFS(); ++bfs_it)
    {
        std::cout << *bfs_it << ", ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    // drawGraph(g,20,"temp");
    auto [shortest_path_distance, shortest_path] = dijkstra<std::string, double>(g, 2u, 4u, [](const double &e) -> double { return e; });
    std::cout << "Distance from 2 to 4: " << shortest_path_distance << std::endl;
    std::cout << "Path from 2 to 4:" << std::endl;
    for (auto &v_id : shortest_path)
    {
        std::cout << v_id << ", ";
    }
    std::cout << std::endl;

    std::tie(shortest_path_distance, shortest_path) = dijkstra<std::string, double>(g, 1u, 0u, [](const double &e) -> double { return e; });
    std::cout << "Distance from 1 to 0: " << shortest_path_distance << std::endl;
    std::cout << "Path from 1 to 0:" << std::endl;
    for (auto &v_id : shortest_path)
    {
        std::cout << v_id << ", ";
    }
    std::cout << std::endl;

    std::tie(shortest_path_distance, shortest_path) = dijkstra<std::string, double>(g, 3u, 0u, [](const double &e) -> double { return e; });
    std::cout << "Distance from 3 to 0: " << shortest_path_distance << std::endl;
    std::cout << "Path from 3 to 0:" << std::endl;
    for (auto &v_id : shortest_path)
    {
        std::cout << v_id << ", ";
    }
    std::cout << std::endl;

    std::tie(shortest_path_distance, shortest_path) = dijkstra<std::string, double>(g, 3u, 1u, [](const double &e) -> double { return e; });
    std::cout << "Distance from 3 to 1: " << shortest_path_distance << std::endl;
    std::cout << "Path from 3 to 1:" << std::endl;
    for (auto &v_id : shortest_path)
    {
        std::cout << v_id << ", ";
    }
    std::cout << std::endl;

    std::tie(shortest_path_distance, shortest_path) = dijkstra<std::string, double>(g, 1u, 3u, [](const double &e) -> double { return e; });
    std::cout << "Distance from 1 to 3: " << shortest_path_distance << std::endl;
    std::cout << "Path from 1 to 3:" << std::endl;
    for (auto &v_id : shortest_path)
    {
        std::cout << v_id << ", ";
    }
    std::cout << std::endl;

    return 0;
}
