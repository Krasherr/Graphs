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

  /*  QApplication a(argc, argv);
    QTextStream out(stdout);
    MainWindow w;
    w.show();

    return a.exec();*/


  Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(0, 3);
    g2.addEdge(1, 2);
    g2.addEdge(1, 3);
    g2.addEdge(2, 3);

    cout << "\nColoring of Graph 2 \n";
    g2.EqualBitColoring();
  //  g2.LFRColoring();
  //  g2.LFRBitColoring();
  //  std::list<std::string> fileList;
  //  fileList = chooseFile(argc, argv);

   //      return 0;

}

/*int main(int, char*[])
{
  vector<boost::dynamic_bitset<>> V;
  const boost::dynamic_bitset<> bZero(1, 1ul);
  V.push_back(bZero);
  std::cout << "bits(0) = " << V[0] << std::endl;

  V[0].resize(3);
  std::cout << "bits(0) po resize = " << V[0] << std::endl;
  for (int u = 0; u < 1; u++){
      std::cout << "Vertex " << u << " --->  Size "
          << V[u].size() << std::endl;
      for (int i = 0; i<=2; i++)
              std::cout << "Vertex " << u << " --->  Color "
              << V[u][i] << std::endl;
  }
}*/

