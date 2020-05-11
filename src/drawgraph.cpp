#include "graph.hpp"
// #include "../lib/gnuplot.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;
template <typename V, typename E>
void drawGraph(Graph<V,E> graph,double radius,std::string filename)
{
    double pi = 3.14 ;
    ofstream data;
    data.open(filename);
    double n = 0;
    for (auto &&value : graph)
    {
        cout << (cos(3.14)) <<"    " << endl;
        n++;
    }
    
    data.close();
}

int main(int argc, char const *argv[])
{
    Graph<int,int> g;
    g.insertVertex(1);
    g.insertVertex(2);
    g.insertVertex(3);
    g.insertVertex(4);
    g.insertVertex(5);
    g.insertVertex(6);
    drawGraph<int,int>(g,20,"data.txt");
    return 0;
}
