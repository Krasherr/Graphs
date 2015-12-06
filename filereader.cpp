#include "filereader.h"

FileReader::FileReader()
{

}

FileReader::~FileReader()
{
}

void FileReader::chooseFile() {
    {
            QList<QString> fileLocalList;
            fileName = QFileDialog::getOpenFileName(0,"Open File",QDir::currentPath(),
                  "All files (*.*)",
                      new QString("All files (*.*)"));

            QFile inputFile(fileName);

            if (inputFile.open(QIODevice::ReadOnly))
            {
               QTextStream in(&inputFile);
               while (!in.atEnd())
               {
                 fileLocalList.push_back(in.readLine());
          //        std::cout << fileList.back() << endl;
               }

            }
         //   std::cout << fileList.at(1).toStdString() << endl;
            inputFile.close();
            fileList=fileLocalList;
        }
}

