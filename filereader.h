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
    QList<QString> getList();


private:
    QString fileName;
    QList<QString> fileList;


};
#endif // FILEREADER
