#include "mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <boost/dynamic_bitset.hpp>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <iostream>
#include "graph.h"
//#include "filereader.h"





int main(int argc, char *argv[])
{

   /* QApplication a(argc, argv);
    QTextStream out(stdout);
    MainWindow w;
    w.show();

    return a.exec();*/


   /* Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(0, 2);
    g2.addEdge(0, 3);
    g2.addEdge(1, 2);
    g2.addEdge(1, 3);
    g2.addEdge(2, 3);

    cout << "\nColoring of Graph 2 \n";
    //g2.LFRColoring();
   // g2.LFRBitColoring();
    g2.EqualBitColoring();*/
  //  std::list<std::string> fileList;
  //  fileList = chooseFile(argc, argv);

   //      return 0;

   /* Graph g2(6);
        g2.addEdge(0, 1);
        g2.addEdge(0, 3);
        g2.addEdge(0, 5);
        g2.addEdge(1, 2);
        g2.addEdge(1, 4);
        g2.addEdge(2, 3);
        g2.addEdge(2, 4);
        g2.addEdge(3, 5);
        g2.addEdge(4, 5);
    g2.EqualBitColoring();*/
    std::clock_t start;
        double duration;



        /* Your algorithm here */


    int gSize = 4;
    Graph g(gSize);
        for (int i = 0; i<gSize; i++){
            for (int j = i+1; j<gSize; j++){
                g.addEdge(i,j);
            }
        }
                start = std::clock();
    g.LFRBitColoring2();
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"printf: "<< duration <<'\n';
}

/*int main(int, char*[])
{
  boost::dynamic_bitset<> b0(2, 0ul);
  std::cout << "bits(0) = " << b0 << std::endl;

  b0.resize(3);
  std::cout << "bits(0) po resize = " << b0 << std::endl;

}
*/
