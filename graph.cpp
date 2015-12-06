#include "graph.h"
#include <vector>
#include <iostream>
#include <QApplication>
#include <QDebug>


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

void Graph::createGraph(QList<QString> strList, int u){
        QMap<int, QVector<QString>> extList;
    for(int it = 0; it<strList.size(); it++) {
        QString str1, str2;
        QVector<QString> v;
            v.push_back(strList.at(it).mid(0,1));
            for (int i=1; i < strList.at(it).size(); ++i ) {
                if (strList.at(it)[i] == '-') {
                    int size = v.size();
                    for (int j = 0; j < size; j++ )
                        v.push_back(v[j]);

                    for (int j = 0; j <  v.size(); j++ ) {
                        QString c;
                        if (j % 2==0)
                            c = "0";
                        else
                            c = "1";
                        v[j].append(c);
                    }
                } else {
                    for (int j = 0; j <  v.size(); j++ ) {
                        v[j].append(strList.at(it).mid(i,1));
                    }
                }
            }
        //    for (int j = 0; j < v.size(); j++ ) {
        //        std::cout << v[j].toStdString() << endl;
        //    }
         extList.insert(it, v);
      /*  for (int c = 0; c<strList.at(it).size(); c++){
       //     char ch = strList.at(it)[c];
             if (strList.at(it)[c] == '0'){
             } else if (strList.at(it)[c]=='1'){
             } else if (strList.at(it)[c] == '-'){
             }
                }*/




    }
    foreach (int key, extList.keys()){
        for (int j = 0; j < extList.value(key).size(); j++ ) {
                    std::cout << extList.value(key)[j].toStdString() << endl;
                }
    }

}
