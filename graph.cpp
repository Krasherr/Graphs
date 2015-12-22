#include "graph.h"
#include <vector>
#include <iostream>
#include <QApplication>
#include <QDebug>
#include "boost/dynamic_bitset.hpp"

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

void Graph::greedyColoring()
{

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

//	cout << result[0];
//	cout << result[1];
}
/*
void Graph::greedyEqualBitColoring()
{
    std::vector<boost::dynamic_bitset<> > result(V);
    //vector <int> result(V);
    // Assign the first color to first vertex
    const boost::dynamic_bitset<> bMinus(1, -1ul);
    int zero = 0, one = 0;
    boost::dynamic_bitset<> b0(1, 0ul);
    result[0] = b0;
    zero++;
    // Initialize remaining V-1 vertices as unassigned
    for (int u = 1; u < V; u++)
        result[u] = bMinus;  // no color is assigned to u

                         // A temporary array to store the available colors. True
                         // value of available[cr] would mean that the color cr is
                         // assigned to one of its adjacent vertices
    /*vector<bool> available(V);
    for (int cr = 0; cr < V; cr++)
        available[cr] = false;*/

    // Assign colors to remaining V-1 vertices

    //Zrobic funkcje ktora na wejscie dostaje liczbe bitow i vector wezlow, zwraca ten sam vector ze zmianami i flaga czy wszystkie pokolorowane, jesli nie to dostaje vector z powrotem z wieksza liczba bitow


    /*for (int u = 1; u < V; u++)
    {
        // Process all adjacent vertices and flag their colors
        // as unavailable
        int bit = 0;
        bool flagZero = false;
        bool flagOne = false;
        list<int>::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != bMinus && (result[*i][bit] = 0 || result[*i][bit] = 1))
            {
                flagZero=true;
                flagOne=true;
            }
               // available[result[*i]] = true;

        // Find the first available color
    /*    int cr;
        for (cr = 0; cr <= V-1; cr++)
            if (available[cr] == false)
                break;

        result[u] = cr; // Assign the found color

                        // Reset the values back to false for the next iteration
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
            if (result[*i] != bMinus)
                available[result[*i]] = false;

    }

    // print the result
    for (int u = 0; u < V; u++)
        std::cout << "Vertex " << u << " --->  Color "
        << result[u] << std::endl;

//	cout << result[0];
//	cout << result[1];
}*/



void Graph::createGraph(QList<QString> strList, int u){
        QVector<QVector<QString>> extList;
        int output;
        int input;

    for(int it = 0; it<strList.size(); it++) {
        QVector<QString> v;
            if (strList.at(it)[0]=='1'||strList.at(it)[0]=='0'){
                v.push_back(strList.at(it).mid(0,1));
            }
            else if (strList.at(it)[0] == '-'){
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
            } else if (strList.at(it)[0] == '.' && strList.at(it)[1] == 'o'){
                output = strList.at(it).mid(3,4).toInt();
            } else if (strList.at(it)[0] == '.' && strList.at(it)[1] == 'i'){
                input = strList.at(it).mid(3,4).toInt();
            }
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
                } else if (strList.at(it)[i] == '1' || strList.at(it)[i] == '0') {
                    for (int j = 0; j <  v.size(); j++ ) {
                        v[j].append(strList.at(it).mid(i,1));
                    }
                }
            }
         if (!v.empty()){
            extList.push_back(v);
        }

    }

    int index = 1;
    int count = 0;
    int key = 0;

    for (QVector<QVector<QString>>::iterator it = extList.begin(); it != extList.end(); ++it){

        count = count + it->count();

    }
    std::cout << "varU: " << u << endl;
    std::cout << "input: " << input << endl;
    std::cout << "output: " << output << endl;
    std::cout << "node count: " << count << endl;
    Graph g(count);

    for(QVector<QVector<QString>>::iterator it = extList.begin(); it != extList.end()-1; ++it) {

        for(QVector<QString>::iterator itt = it->begin(); itt != it->end(); ++itt) {
             int key1 = key +1;
             std::cout << key << " : "<< itt->toStdString()<<endl;

             for(QVector<QVector<QString>>::iterator ittt = extList.begin()+index; ittt != extList.end(); ++ittt) {
                 for(QVector<QString>::iterator itttt = ittt->begin(); itttt != ittt->end(); ++itttt) {
                      std::cout << key1 << " : " << itttt->toStdString()<<endl;
                      if (itt->mid(0,input-u)==itttt->mid(0,input-u)&&itt->mid(input,input+output)!=itttt->mid(input,input+output)){
                          g.addEdge(key,key1);

                          cout << "krawedz pomiedzy nodem " << key << " a nodem " << key1 << endl;
                      }else {

                      } key1++;
                 }
             } key++;
        }
    index++;
    }
    g.greedyColoring();


}
