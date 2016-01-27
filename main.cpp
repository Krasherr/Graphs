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

    Graph g2;
    g2.setV(4);
    g2.printGraph();
    g2.addEdge(0, 2);
    g2.addEdge(0, 3);
    g2.addEdge(1, 2);
    g2.addEdge(1, 3);
    g2.addEdge(2, 3);
    g2.printGraph();
    cout << "\nColoring of Graph 2 \n";
   // g2.MaxCutRandomBitColoring();
}
// g2.LFRBitColoring();
// g2.LFRBitColoring();*/
//  std::list<std::string> fileList;
//  fileList = chooseFile(argc, argv);

//      return 0;
/*
     Graph g2;
          g2.setV(6);
         g2.addEdge(0, 1);
         g2.addEdge(0, 3);
         g2.addEdge(0, 5);
         g2.addEdge(1, 2);
         g2.addEdge(2, 3);
         g2.addEdge(2, 4);
         g2.addEdge(3, 4);
         g2.addEdge(3, 5);
         g2.addEdge(4, 5);
         g2.printGraph();
     g2.LFRColoring2();*/


/*      cout << "po set" << endl;
  //g2.printGraph();
 std::clock_t start;
 double duration;






 int gSize = 100;
 Graph g(gSize);
 for (int i = 0; i<gSize; i++) {
     for (int j = i+1; j<gSize; j++) {
         //if (j%3==0)
         g.addEdge(i,j);
     }
 }
 //g.printGraph();
 start = std::clock();
 g.MaxCutRandomBitColoring();
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


using namespace std;


ifstream infile ("graph.txt");
ofstream outfile ("sets.txt");

/*int main(int argc, char *argv[])
{

    MaximumIndependentSet maxSet;
 //Read Graph
 cout<<"Independent Set Algorithm."<<endl;

 infile>>n;
 vector< vector<int> > graph;
 for(i=0; i<n; i++)
 {
  vector<int> row;
  for(j=0; j<n; j++)
  {
   infile>>edge;
   row.push_back(edge);
  }
  graph.push_back(row);
 }
 //Find Neighbors

 Graph g2;
      g2.setV(6);
     g2.addEdge(0, 1);
     g2.addEdge(0, 3);
     g2.addEdge(0, 5);
     g2.addEdge(1, 2);
     g2.addEdge(2, 3);
     g2.addEdge(2, 4);
     g2.addEdge(4, 5);
     g2.printGraph();
 /*vector<int> cover = maxSet.process(g2.getAdj(), g2.getV(), g2.getV());
for(int j=0; j<cover.size(); j++) if(cover[j]==0) cout<<j+1<<" ";

 system("PAUSE");
 return 0;
     g2.MaxCutRandomBitColoring();
}*/


