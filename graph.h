#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <QApplication>
#include "boost/dynamic_bitset.hpp"

using namespace std;
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
    vector<int> color;
    vector<int> tmp;
    vector<int> bitSize;
    vector<int> bitSizeMin;
    vector<bool> marked;
    vector<boost::dynamic_bitset<> > colorBit;
public:
    // Constructor and destructor
    Graph();
    Graph(int V) { this->V = V; adj = new list<int>[V];}
    ~Graph() { delete[] adj;}

    // function to add an edge to graph
    void addEdge(int v, int w);
    // Prints greedy coloring of the vertices
    void LFRColoring();
    void LFRBitColoring();
    void createGraph(QList<QString> strList, int u);
    int getTmp();
    int getBitTmp();


};

#endif // GRAPH_H
