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
    QList<QString> getList()
    {
        return fileList;
    }
    int getInput()
    {
        return input;
    }
    int getOutput()
    {
        return output;
    }
    QVector<QVector<QString>> createNodes(QList<QString> strList);


private:
    QString fileName;
    QList<QString> fileList;
    int output;
    int input;


};
#endif // FILEREADER
