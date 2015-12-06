#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <QApplication>

using namespace std;
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
public:
    // Constructor and destructor
    Graph();
    Graph(int V) { this->V = V; adj = new list<int>[V]; }
    ~Graph() { delete[] adj; }

    // function to add an edge to graph
    void addEdge(int v, int w);

    // Prints greedy coloring of the vertices
    void greedyColoring();
    void createGraph(QList<QString> strList, int u);
};

#endif // GRAPH_H
