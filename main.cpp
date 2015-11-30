#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <boost/dynamic_bitset.hpp>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
//#include "filereader.h"





int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTextStream out(stdout);
    MainWindow w;
    w.show();

    return a.exec();

/*
    Graph g2(5);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(1, 2);
    g2.addEdge(1, 4);
    g2.addEdge(2, 4);
    g2.addEdge(4, 3);
    cout << "\nColoring of Graph 2 \n";
    g2.greedyColoring();
    std::list<std::string> fileList;
    fileList = chooseFile(argc, argv);

         return 0;*/

}
