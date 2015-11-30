#include "graph.h"
#include <vector>
#include <iostream>
using namespace std;


void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors
void Graph::greedyColoring()
{
    //vector<boost::dynamic_bitset<> > result(V,boost::dynamic_bitset<>(V/2));
    vector <int> result(V);
    // Assign the first color to first vertex
    result[0] = V-1;

    // Initialize remaining V-1 vertices as unassigned
    for (int u = 1; u < V; u++)
        result[u] = -1;  // no color is assigned to u

                         // A temporary array to store the available colors. True
                         // value of available[cr] would mean that the color cr is
                         // assigned to one of its adjacent vertices
    vector<bool> available(V);
    for (int cr = 0; cr < V; cr++)
        available[cr] = false;

    // Assign colors to remaining V-1 vertices
    for (int u = 1; u < V; u++)
    {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = true;

        // Find the first available color
        int cr;
        for (cr = V-1; cr >= 0; cr--)
            if (available[cr] == false)
                break;

        result[u] = cr; // Assign the found color

                        // Reset the values back to false for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != -1)
                available[result[*i]] = false;
    }

    // print the result
    for (int u = 0; u < V; u++)
        std::cout << "Vertex " << u << " --->  Color "
        << result[u] << std::endl;

//	cout << result[0];
//	cout << result[1];
}
