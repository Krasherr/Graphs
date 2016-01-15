#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <QApplication>
#include "boost/dynamic_bitset.hpp"

using namespace std;
class Graph {

public:
    // Constructor and destructor
    Graph();
    Graph(int V)
    {
        this->V = V;
        adjacentNodes = new list<int>[V];
    }
    ~Graph()
    {
        delete[] adjacentNodes;
    }

    // function to add an edge to graph
    void addEdge(int v, int w);
    // Prints greedy coloring of the vertices
    void LFRColoring();
    void LFRBitColoring();
    void LFRBitColoring2();
    void EqualBitColoring();
    int getTmp();
    int getBitTmp();
    int getV()
    {
        return V;
    }
    void setV(int count)
    {
        this->V = count;
        adjacentNodes = new list<int>[V];
    }
    void addNode()
    {
        this->V++;
        adjacentNodes->resize(V);
    }

private:

    int V;    // No. of vertices
    list<int> *adjacentNodes;    // A dynamic array of adjacency lists
    vector<int> color;
    vector<int> tmp;
    vector<int> bitSize;
    int bitSizeMin;
    vector<bool> marked;
    vector<boost::dynamic_bitset<> > colorBit;
};

#endif // GRAPH_H
