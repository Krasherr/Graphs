#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <QFileDialog>
#include <QApplication>
#include <iostream>
#include <QMessageBox>
#include <QTextStream>

//std::list<std::string> chooseFile(int argc, char *argv[]){
class FileReader {

public:
    FileReader();
    ~FileReader();

    void chooseFile();

private:
    QString fileName;
    std::list<std::string> fileList;


};
#endif // FILEREADER
