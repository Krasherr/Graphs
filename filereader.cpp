#include "filereader.h"

FileReader::FileReader()
{

}

FileReader::~FileReader()
{
}

void FileReader::chooseFile() {
    {

            fileName = QFileDialog::getOpenFileName(0,"Open File",QDir::currentPath(),
                  "All files (*.*)",
                      new QString("All files (*.*)"));

            QFile inputFile(fileName);

            if (inputFile.open(QIODevice::ReadOnly))
            {
               QTextStream in(&inputFile);
               while (!in.atEnd())
               {
                  fileList.push_back(in.readLine());
          //        std::cout << fileList.back() << endl;
               }

            }
            inputFile.close();

        }
}

QList<QString> FileReader::getList() {
    return fileList;
}
