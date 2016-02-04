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
    }

    // function to add an edge to graph
    void addEdge(int v, int w);
    void printGraph()
    {
        for (int i=0; i<adjacentNodes.size(); i++) {
            for (int j=0; j<adjacentNodes[i].size(); j++) {
                cout << adjacentNodes[i][j];
            }
            cout << endl;
        }
    }

    // Prints greedy coloring of the vertices
    void LFRColoring();
    void LFRBitColoring();
    void LFRColoring2();
    void EqualBitColoring();
    void MISBitColoring();
    void MISColoring();
    void graphToFile(const vector<boost::dynamic_bitset<>> &colorBit,const vector<int> &bitSize,  const int &bitSizeMin);
    void graphToFile(const vector<int> &color);
    int getTmp(const vector<int> &color, const vector<int> &tmp, const int &V);
    int getLFRBitTmp(const vector<int> &tmp, const int &V, const vector<int> &bitSize, const vector<int> &marked, const int &bitSizeMin);
    int getEqualBitTmp(const vector<int> &tmp, const int &V, const vector<int> &bitSize, const vector<int> &marked, const int &bitSizeMin);

    int getV()
    {
        return V;
    }
    vector<vector <int>> getAdjacentNodes()
    {
        return adjacentNodes;
    }

    void setV(const int &count)
    {
        if (count > V)
        for (int i = 0; i<V; i++){
            for (int j = 0; j<count - V; j++){
                adjacentNodes[i].push_back(0);
            }
        }
        this -> V = count;

        adjacentNodes.resize(count, std::vector<int>(count,0));
        for (int i = 0; i<V; i++){
             adjacentNodes[i].resize(count);
        }

    }

    void addNode()
    {
        for (int i = 0; i<V; i++){
            adjacentNodes[i].push_back(0);
        }
        this->V++;
        vector<int> adjacentNodesTmp (V,0);
        adjacentNodes.push_back(adjacentNodesTmp);
    }


private:

    int V;    // No. of vertices
    std::vector<std::vector<int>> adjacentNodes;    // A dynamic array of adjacency lists
    vector<int> edgeValue;

};

#endif // GRAPH_H
