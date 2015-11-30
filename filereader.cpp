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
                  fileList.push_back(in.readLine().toStdString());
          //        std::cout << fileList.back() << endl;
               }

            }
            inputFile.close();
            std::cout << "2" << endl;
            return;
            std::cout << "3" << endl;
 //           return fileList;
        }
}

std::list<std::string> FileReader::getList() {
    return fileList;
}
