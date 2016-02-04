#include "mainwindow.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <boost/dynamic_bitset.hpp>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include "graph.h"
#include <fstream>
#include "maximumindependentset.h"
//#include "filereader.h"





int main(int argc, char *argv[])
{

    /*     QApplication a(argc, argv);
         QTextStream out(stdout);
         MainWindow w;
         w.show();

         return a.exec();
    }*/

  /*  Graph g2;
    g2.setV(4);
    g2.printGraph();
    g2.addEdge(0, 2);
    g2.addEdge(0, 3);
    g2.addEdge(1, 2);
    g2.addEdge(1, 3);
    g2.addEdge(2, 3);
    g2.printGraph();
    cout << "\nColoring of Graph 2 \n";*/
    Graph g2;
    g2.setV(11);
    g2.addEdge(0,1);
    g2.addEdge(0,3);
    g2.addEdge(0,6);
    g2.addEdge(0,8);
    g2.addEdge(1,2);
    g2.addEdge(1,5);
    g2.addEdge(1,7);
    g2.addEdge(2,4);
    g2.addEdge(2,6);
    g2.addEdge(2,9);
    g2.addEdge(3,4);
    g2.addEdge(3,5);
    g2.addEdge(3,9);
    g2.addEdge(4,7);
    g2.addEdge(4,8);
    g2.addEdge(5,10);
    g2.addEdge(6,10);
    g2.addEdge(7,10);
    g2.addEdge(8,10);
    g2.addEdge(9,10);
    std::clock_t start;
    double duration;
    start = std::clock();
    g2.LFRBitColoring();
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"printf: "<< duration <<'\n';
 }
