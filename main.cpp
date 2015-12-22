#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <boost/dynamic_bitset.hpp>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include "graph.h"
//#include "filereader.h"





int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QTextStream out(stdout);
    MainWindow w;
    w.show();

    return a.exec();


  /*  Graph g2(7);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(0, 4);
    g2.addEdge(0, 5);
    g2.addEdge(1, 3);
    g2.addEdge(1, 5);
    g2.addEdge(1, 6);
    g2.addEdge(2, 3);
    g2.addEdge(2, 4);
    g2.addEdge(2, 5);
    g2.addEdge(3, 5);
    g2.addEdge(3, 6);
    g2.addEdge(4, 6);
    cout << "\nColoring of Graph 2 \n";
    g2.greedyColoring();
  //  std::list<std::string> fileList;
  //  fileList = chooseFile(argc, argv);

   //      return 0;
*/
}

/*int main(int, char*[])
{
  boost::dynamic_bitset<> b0(2, 0ul);
  std::cout << "bits(0) = " << b0 << std::endl;

  b0.resize(3);
  std::cout << "bits(0) po resize = " << b0 << std::endl;

}
*/
