#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <QApplication>

using namespace std;
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
    vector<int> color;
    vector<int> tmp;
public:
    // Constructor and destructor
    Graph();
    Graph(int V) { this->V = V; adj = new list<int>[V];}
    ~Graph() { delete[] adj;}

    // function to add an edge to graph
    void addEdge(int v, int w);
    const static int MAX = 100;
    // Prints greedy coloring of the vertices
    void greedyColoring();
    void greedyEqualBitColoring();
    void createGraph(QList<QString> strList, int u);
    int getTmp();


};

#endif // GRAPH_H
