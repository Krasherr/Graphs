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






int main(int argc, char *argv[])
{

         QApplication a(argc, argv);
         QTextStream out(stdout);
         MainWindow w;
         w.show();

         return a.exec();
    }

