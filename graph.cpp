#include "graph.h"
#include <vector>
#include <iostream>
#include <QApplication>
#include <QDebug>
#include "boost/dynamic_bitset.hpp"

Graph::Graph()
{

}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

// Assigns colors (starting from 0) to all vertices and prints
// the assignment of colors

int Graph::getTmp()
{
    int max = -1;
    int max_i;
    for (int i =0; i < V; i++)
        if (color[i] == -1)
            if (tmp[i]>max)
            {
                max = tmp[i];
                max_i = i;
            }
    return max_i;
}

int Graph::getBitTmp()
{
    int max = -1;
    int max_i;
    for (int i =0; i < V; i++)
        if ((color[i] == -1 || marked[i]==true) && bitSize[i] == *min_element(bitSizeMin.begin(), bitSizeMin.end()))
            if (tmp[i]>max)
            {
                max = tmp[i];
                max_i = i;
            }
    return max_i;
}


void Graph::LFRColoring()
{
    list<int> *adj = Graph::adj;
     //vector<boost::dynamic_bitset<> > result(V,boost::dynamic_bitset<>(V/2));
    int uncolored=0;
    //tmp = new vector <int> (V);

    // Assign the first color to first vertex
    for (int u = 0; u<V; u++){
        tmp.push_back(adj[u].size());
    }

    // Initialize remaining V-1 vertices as unassigned
    for (int u = 0; u < V; u++){
        uncolored++;
        color.push_back(-1);  // no color is assigned to u
    }
                         // A temporary array to store the available colors. True
                         // value of available[cr] would mean that the color cr is
                         // assigned to one of its adjacent vertices
    vector<bool> used(V);
    for (int cr = 0; cr < V; cr++)
        used[cr] = false;

    // Assign colors to remaining V-1 vertices
    while (uncolored>0)
    {
        int u;
        // Process all adjacent vertices and flag their colors
        // as unavailable
        u = getTmp();
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (color[*i] != -1)
                used[color[*i]] = true;

        // Find the first available color
        int cr;
        for (cr = 0; cr <= V-1; cr++)
            if (used[cr] == false)
                break;

        color[u] = cr; // Assign the found color
        uncolored--;

                        // Reset the values back to false for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (color[*i] != -1)
                used[color[*i]] = false;
    }

    // print the result
    for (int u = 0; u < V; u++)
        std::cout << "Vertex " << u << " --->  Color "
        << color[u] << std::endl;
    tmp.clear();
    color.clear();

//	cout << result[0];
//	cout << result[1];
}

void Graph::LFRBitColoring()
{
    list<int> *adj = Graph::adj;
    const boost::dynamic_bitset<> bZero(1, 0ul);
    int uncolored=0;
    for (int u = 0; u<V; u++){
        tmp.push_back(adj[u].size());
    }

    //vector <int> result(V);
    // Assign the first color to first vertex

    //int zero = 0, one = 0;
    for (int u = 0; u < V; u++){
        uncolored++;
        color.push_back(-1);
        colorBit.push_back(bZero);  // no color is assigned to u
    }


    vector<bool> used(2);
    for (int cr = 0; cr < 2; cr++)
        used[cr] = false;

    for (int cr = 0; cr < V; cr++){
        bitSize.push_back(0);
        bitSizeMin.push_back(0);
        marked.push_back(true);
    }

    cout << "po ustawieniu kolorow na -1" << endl;
    //result[0] = b0;
   // zero++;
    // Initialize remaining V-1 vertices as unassigned
    while (uncolored>0)
    {
                cout << "petla, uncolored: " << uncolored << endl;
        int u;
        vector<std::list<int>::iterator> it;
        // Process all adjacent vertices and flag their colors
        // as unavailable
        u = getBitTmp();
         cout << "petla, vector: " << u << endl;
        list<int>::iterator i;

        if (colorBit[u].size()<bitSize[u]+1) {
            colorBit[u].resize(bitSize[u]+1);
             for (i = adj[u].begin(); i != adj[u].end(); ++i){
                 if (color[*i]==true)
                     it.push_back(i);
             }
             for (int j = 0; j < it.size(); j++){
                 adj[u].erase(it[j]);
             }
             break;
        }

            for (i = adj[u].begin(); i != adj[u].end(); ++i){
               // cout << "petla, vector: " << *i << endl;
                if (used[0]==true && used[1]==true){
                                       break;
                                   }
                if (color[*i] != -1){
                   if (colorBit[*i][bitSize[u]]==0)
                       used[0] = true;
                   else if (colorBit[*i][bitSize[u]]==1)
                       used[1] = true;
                }
            }


            // Find the first available color
            int cr;
            for (cr = 0; cr <= 2; cr++)
                if (used[cr] == false)
                    break;


            cout << "kolor dostepny: " << cr << endl;
            if (cr == 0 || cr == 1)
            {   colorBit[u][bitSize[u]] = cr; // Assign the found color
                color[u]=1;
                marked[u]=false;
                uncolored--;
                bitSizeMin[u]=9999999;
            } else {
                colorBit[u][bitSize[u]] = 0;
                bitSize[u]=bitSize[u]+1;
                bitSizeMin[u]=bitSize[u];

                cout << "bitSize: " << bitSize[u]<<endl;
                colorBit[u].resize( bitSize[u]+1);

            }

            if (marked[u]==true && bitSize[u]>0){

                for (i = adj[u].begin(); i != adj[u].end(); ++i){

                    if (bitSize[*i]>bitSize[u]-2 && color[*i] != -1 && colorBit[*i][bitSize[u]-1]==colorBit[u][bitSize[u]-1] ){

                        if (bitSize[*i] < bitSize[u])
                        {
                            bitSize[*i]=bitSize[u];
                            bitSizeMin[*i]=bitSize[u];
                            marked[*i]=true;
                            uncolored++;
                            cout << "powiekszam wezel numer: " << *i<<endl;
                        }

                    } else {

                        if (color[*i] != -1){
                            it.push_back(i);
                            cout << "usuwam wezel numer: " << *i<<endl;
                        }

                    }

            }

            for (int j = 0; j < it.size(); j++){
                adj[u].erase(it[j]);
            }

                            // Reset the values back to false for the next iteration
           // if (!adj[u].empty())
         //    for (i = adj[u].begin(); i != adj[u].end(); ++i){
          //          if (color[*i] != -1){
                        used[0] = false;
                        used[1] = false;
           //         }
            // }
        }
    }

    //cout << "wyjscie z petli" << endl;

    for (int u = 0; u < V; u++){
        std::cout << "Vertex " << u << " --->  Size "
            << colorBit[u].size() << std::endl;
        for (int i = 0; i<=*max_element(bitSize.begin(), bitSize.end()); i++)
            if(i>bitSize[u]){
                std::cout << "Vertex " << u << " --->  Color -"
                 << std::endl;
            } else
                std::cout << "Vertex " << u << " --->  Color "
                << colorBit[u][i] << std::endl;
    }

    colorBit.clear();
    color.clear();
    bitSize.clear();
    marked.clear();
}

void Graph::EqualBitColoring()
{
    list<int> *adj = Graph::adj;
    const boost::dynamic_bitset<> bZero(1, 0ul);
    int uncolored=0;
    for (int u = 0; u<V; u++){
        tmp.push_back(adj[u].size());
    }

    //vector <int> result(V);
    // Assign the first color to first vertex

    int zero = 0, one = 0;
    for (int u = 0; u < V; u++){
        uncolored++;
        color.push_back(-1);
        colorBit.push_back(bZero);  // no color is assigned to u
    }


    vector<bool> used(2);
    for (int cr = 0; cr < 2; cr++)
        used[cr] = false;

    for (int cr = 0; cr < V; cr++){
        bitSize.push_back(0);
        bitSizeMin.push_back(0);
        marked.push_back(true);
    }

    cout << "po ustawieniu kolorow na -1" << endl;
    //result[0] = b0;
   // zero++;
    // Initialize remaining V-1 vertices as unassigned
    while (uncolored>0)
    {
                cout << "petla, uncolored: " << uncolored << endl;
        int u;
        vector<std::list<int>::iterator> it;
        // Process all adjacent vertices and flag their colors
        // as unavailable
        u = getBitTmp();
         cout << "petla, vector: " << u << endl;
        list<int>::iterator i;

        if (colorBit[u].size()<bitSize[u]+1) {
            colorBit[u].resize(bitSize[u]+1);
             for (i = adj[u].begin(); i != adj[u].end(); ++i){
                 if (color[*i]==true)
                     it.push_back(i);
             }
             for (int j = 0; j < it.size(); j++){
                 adj[u].erase(it[j]);
             }
        } else {

            for (i = adj[u].begin(); i != adj[u].end(); ++i){
               // cout << "petla, vector: " << *i << endl;
                if (color[*i] != -1){
                   if (colorBit[*i][bitSize[u]]==0)
                       used[0] = true;
                   else if (colorBit[*i][bitSize[u]]==1)
                       used[1] = true;
                }
            }


            // Find the first available color
           /* int cr;
            for (cr = 0; cr <= 2; cr++)
                if (used[cr] == false)
                    break;*/


          //  cout << "kolor dostepny: " << cr << endl;
            if (used[0] == false && used[1] == false)
            {
                if (zero<=one){
                    colorBit[u][bitSize[u]] = 0; // Assign the found color
                    color[u]=1;
                    marked[u]=false;
                    uncolored--;
                    zero++;
                    bitSizeMin[u]=99999999;
                } else {
                    colorBit[u][bitSize[u]] = 1; // Assign the found color
                    color[u]=1;
                    marked[u]=false;
                    uncolored--;
                    one++;
                    bitSizeMin[u]=99999999;
                }
            } else if (used[0] == false){
                colorBit[u][bitSize[u]] = 0; // Assign the found color
                color[u]=1;
                marked[u]=false;
                uncolored--;
                zero++;
                bitSizeMin[u]=99999999;
            } else if (used[1] == false){
                colorBit[u][bitSize[u]] = 1; // Assign the found color
                color[u]=1;
                marked[u]=false;
                uncolored--;
                one++;
                bitSizeMin[u]=9999999;
            } else {
                if (zero<=one){
                     colorBit[u][bitSize[u]] = 0;
                     zero++;
                } else {
                     colorBit[u][bitSize[u]] = 1;
                     one++;
                }

                bitSize[u]=bitSize[u]+1;
                bitSizeMin[u]=bitSize[u];

                cout << "bitSize: " << bitSize[u]<<endl;
                colorBit[u].resize( bitSize[u]+1);
            }
            if (marked[u]==true && bitSize[u]>0){

                for (i = adj[u].begin(); i != adj[u].end(); ++i){

                    if (bitSize[*i]>bitSize[u]-2 && color[*i] != -1 && colorBit[*i][bitSize[u]-1]==colorBit[u][bitSize[u]-1] ){

                        if (bitSize[*i] < bitSize[u])
                        {
                            bitSize[*i]=bitSize[u];
                            bitSizeMin[*i]=bitSize[u];
                            marked[*i]=true;
                            color[u]=-1;
                            uncolored++;
                            cout << "powiekszam wezel numer: " << *i<<endl;
                        }

                    } else {

                        if (color[*i] != -1){
                            it.push_back(i);
                            cout << "usuwam wezel numer: " << *i<<endl;
                        }

                    }
                }
            }

            for (int j = 0; j < it.size(); j++){
                adj[u].erase(it[j]);
            }

                            // Reset the values back to false for the next iteration
           // if (!adj[u].empty())
             for (i = adj[u].begin(); i != adj[u].end(); ++i){
                    if (color[*i] != -1){
                        used[0] = false;
                        used[1] = false;
                    }
             }
        }
    }

    //cout << "wyjscie z petli" << endl;

    for (int u = 0; u < V; u++){
        std::cout << "Vertex " << u << " --->  Size "
            << colorBit[u].size() << std::endl;
        for (int i = 0; i<=*max_element(bitSize.begin(), bitSize.end()); i++)
            if(i>bitSize[u]){
                std::cout << "Vertex " << u << " --->  Color -"
                 << std::endl;
            } else
                std::cout << "Vertex " << u << " --->  Color "
                << colorBit[u][i] << std::endl;
    }

    colorBit.clear();
    color.clear();
    bitSize.clear();
    marked.clear();
}
