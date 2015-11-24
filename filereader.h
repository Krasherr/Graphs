#ifndef FILEREADER
#define FILEREADER

#endif // FILEREADER

#include <string>
#include <QFileDialog>
#include <QApplication>
#include <iostream>
#include <QMessageBox>
#include <QTextStream>

using namespace std;
std::list<std::string> chooseFile(int argc, char *argv[]){

    QApplication app(argc,argv);
    QString fileName;
    fileName = QFileDialog::getOpenFileName(0,"Open File",QDir::currentPath(),
          "All files (*.*)",
              new QString("All files (*.*)"));

    QFile inputFile(fileName);
    std::list<std::string> fileList;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          fileList.push_back(in.readLine().toStdString());
          cout << fileList.back() << endl;
       }
       inputFile.close();
    }
    return fileList;
}
