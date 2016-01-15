#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <array>
#include <iostream>
#include <QApplication>
#include "boost/dynamic_bitset.hpp"

using namespace std;
class Graph {

public:
    // Constructor and destructor
    Graph();
    Graph(const int& V) : V(V)
    {
        adjacentNodes.resize(V, std::vector<int>(V,0));

    }
    ~Graph()
    {
        //delete[] adjacentNodes;
    }

    // function to add an edge to graph
    void addEdge(int v, int w);
    void printGraph(){
        for (int i=0; i<V; i++){
            for (int j=0; j<V; j++){
                cout << adjacentNodes[i][j];
            }
            cout << endl;
        }
    }

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
/*    void setV(int count)
    {
        this->V = count;
        adjacentNodes = new list<int>[V];
    }
    void addNode()
    {
        this->V++;
        adjacentNodes->resize(V);
    }*/

private:

    int V;    // No. of vertices
    std::vector<std::vector<int>> adjacentNodes;    // A dynamic array of adjacency lists
    vector<int> color;
    vector<int> tmp;
    vector<int> bitSize;
    int bitSizeMin;
    vector<bool> marked;
    vector<boost::dynamic_bitset<> > colorBit;
};

#endif // GRAPH_H
