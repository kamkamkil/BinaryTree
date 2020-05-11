#include "graph.hpp"
// #include "../lib/gnuplot.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;
template <typename V, typename E>
void drawGraph(Graph<V, E> &graph, double radius, std::string filename)
{
    double pi = 3.14 * 2;
    auto getX = [&](double id) -> double { return radius * cos(id * (pi / (double)graph.nrOfVertices())); };
    auto getY = [&](double id) -> double { return radius * sin(id * (pi / (double)graph.nrOfVertices())); };
    ofstream data;
    data.open(filename);
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
            data<< getX(node) << "    " << getY(node) << "    " << getX(value) << "    " << getY(value) << endl;
        }
    }
    data.close();
    data.open("script" + filename);
    data << "plot \"" << filename << "\"  index 0 with labels point  pt 7 offset char 1,1,\\"<<endl;
    data <<"\"" << filename << "\" index 1  using 1:2:($3-$1):($4-$2)  with vectors head filled" <<endl;
    data.close();
}

int main(int argc, char const *argv[])
{
    Graph<int, int> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertEdge(2, 3, 0);
    g.insertEdge(1, 1, 0);
    g.insertEdge(1, 2, 0);
    g.insertEdge(3, 4, 0);
    g.insertEdge(1, 4, 0);
    drawGraph<int, int>(g, 20, "data.txt");
    return 0;
}
