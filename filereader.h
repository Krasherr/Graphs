#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <QFileDialog>
#include <QApplication>
#include <iostream>
#include <QMessageBox>
#include <QTextStream>

class FileReader {

public:
    FileReader();
    ~FileReader();

    void chooseFile();
    std::list<std::string> getList();


private:
    QString fileName;
    std::list<std::string> fileList;


};
#endif // FILEREADER
