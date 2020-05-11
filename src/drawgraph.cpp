#include "graph.hpp"
// #include "../lib/gnuplot.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <functional>
using namespace std;
template <typename V, typename E>
void drawGraph(Graph<V, E> &graph, double radius, std::string filename)
{
    double pi = 3.14 * 2;
    auto getX = [&](double id) -> double { return radius * cos(id * (pi / (double)graph.nrOfVertices())); };
    auto getY = [&](double id) -> double { return radius * sin(id * (pi / (double)graph.nrOfVertices())); };
    ofstream data;
    data.open("graph_out/" + filename);
    double n = 0;
    for (auto &&value : graph)
    {
        data << getX(n) << "    " << getY(n);
        data << "    \"" << value << "\"" << endl;
        n++;
    }
    data << endl;
    data << endl;

    for (size_t node = 0; node < graph.nrOfVertices(); node++)
    {
        for (auto &&value : graph.neighbours(node))
        {
            data << getX(node) << "    " << getY(node) << "    " << getX(value) << "    " << getY(value) << endl;
        }
    }
    data << endl;
    data << endl;
    for (size_t node = 0; node < graph.nrOfVertices(); node++)
    {
        for (auto &&value : graph.neighbours(node))
        {
            data << (getX(node) + 4 * getX(value)) / 5 << "   " << (getY(node) + 4 * getY(value)) / 5 << "     \" " << graph.edgeLabel(node, value) << "\"" << endl;
        }
    }
    data.close();
    data.open("graph_out/script" + filename);
    data << "set key off" << endl;
    data << "plot \"" << filename << "\"  index 0 with labels point  pt 7 offset char 0,1,\\" << endl;
    data << "\"" << filename << "\" index 1  using 1:2:($3-$1):($4-$2)  with vectors head filled,\\" << endl;
    data << "\"" << filename << "\" index 2 using 1:2:3 with labels boxed tc lt 1 " << endl;
    data.close();
}
template <typename V, typename E>
void animatePath(Graph<V, E> &graph, double radius, std::string filename, size_t vertex)
{
    double pi = 3.14 * 2;
    auto getX = [&](double id) -> double { return radius * cos(id * (pi / (double)graph.nrOfVertices())); };
    auto getY = [&](double id) -> double { return radius * sin(id * (pi / (double)graph.nrOfVertices())); };
    ofstream data;
    string baseGraph = "baseGraph" + filename;
    data.open("graph_out/" + baseGraph);
    double n = 0;
    for (auto &&value : graph)
    {
        data << getX(n) << "    " << getY(n);
        data << "    \"" << value << "\"" << endl;
        n++;
    }
    data << endl;
    data << endl;

    for (size_t node = 0; node < graph.nrOfVertices(); node++)
    {
        for (auto &&value : graph.neighbours(node))
        {
            data << getX(node) << "    " << getY(node) << "    " << getX(value) << "    " << getY(value) << endl;
        }
    }
    data << endl;
    data << endl;
    for (size_t node = 0; node < graph.nrOfVertices(); node++)
    {
        for (auto &&value : graph.neighbours(node))
        {
            data << (getX(node) + 4 * getX(value)) / 5 << "   " << (getY(node) + 4 * getY(value)) / 5 << "     \" " << graph.edgeLabel(node, value) << "\"" << endl;
        }
    }
    data.close();
    string baseGraphStript = "baseGraphScript" + filename;
    data.open("graph_out/" + baseGraphStript);
    data << "set key off" << endl;
    data << "plot \"" << baseGraph << "\"  index 0 with labels point  pt 7 offset char 0,1,\\" << endl;
    data << "\"" << baseGraph << "\" index 1  using 1:2:($3-$1):($4-$2)  with vectors head filled,\\" << endl;
    data << "\"" << baseGraph << "\" using 1:2:3 with labels boxed tc lt 1,\\ " << endl;
    data.close();
    //===================
    vector<size_t> result = BFS(graph, vertex);
    data.open("graph_out/" + filename);
    for (size_t i = 1; i < result.size(); i++)
    {
        for (size_t k = 1; k < i; k++)
        {
            data << getX(result[k]) << "    " << getY(result[k]) << "    " << getX(result[k - 1]) << "    " << getY(result[k - 1]) << endl;
        }
        data << endl
             << endl;
    }
    data.close();
    data.open("graph_out/stript" + filename);
    data << "load \"" << baseGraphStript << "\" ,\\" << endl;
    data << "\"" << filename << "\" index 0 using 1:2:($3-$1):($4-$2) with vectors head filled tc lt 1" << endl;
}
int main(int argc, char const *argv[])
{
    Graph<std::string, int> g;
    g.insertVertex("zero");
    g.insertVertex("jeden");
    g.insertVertex("dwa");
    g.insertVertex("trzy");
    g.insertVertex("cztery");
    g.insertVertex("pięć");
    g.insertVertex("sześć");
    g.insertVertex("siedem");
    g.insertEdge(0, 1, 11);
    g.insertEdge(0, 3, 12);
    g.insertEdge(1, 4, 13);
    g.insertEdge(1, 2, 14);
    g.insertEdge(2, 1, 15);
    g.insertEdge(2, 7, 16);
    g.insertEdge(3, 4, 17);
    g.insertEdge(4, 3, 18);
    g.insertEdge(4, 5, 19);
    g.insertEdge(5, 6, 112);
    g.insertEdge(6, 7, 134);
    g.insertEdge(7, 2, 145);
    g.insertEdge(7, 6, 167);
    // drawGraph<string,int>(g,20,"temp.txt");
    animatePath<std::string, int>(g, 20, "_test.txt", 0);
    return 0;
}
