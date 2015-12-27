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


QVector<QVector<QString>> FileReader::createNodes(QList<QString> strList) {
            QVector<QVector<QString>> extList;

        for(int it = 0; it<strList.size(); it++) {
            QVector<QString> v;
                if (strList.at(it)[0]=='1'||strList.at(it)[0]=='0'){
                    v.push_back(strList.at(it).mid(0,1));
                }
                else if (strList.at(it)[0] == '-'){
                        v.push_back("0");
                        v.push_back("1");
                } else if (strList.at(it)[0] == '.' && strList.at(it)[1] == 'o'){
                    output = strList.at(it).mid(3,4).toInt();
                } else if (strList.at(it)[0] == '.' && strList.at(it)[1] == 'i'){
                    input = strList.at(it).mid(3,4).toInt();
                }
                for (int i=1; i < strList.at(it).size(); ++i ) {
                    if (strList.at(it)[i] == '-') {
                        int size = v.size();
                        for (int j = 0; j < size; j++ )
                            v.push_back(v[j]);

                        for (int j = 0; j <  v.size(); j++ ) {
                            QString c;
                            if (j % 2==0)
                                c = "0";
                            else
                                c = "1";
                            v[j].append(c);
                        }
                    } else if (strList.at(it)[i] == '1' || strList.at(it)[i] == '0') {
                        for (int j = 0; j <  v.size(); j++ ) {
                            v[j].append(strList.at(it).mid(i,1));
                        }
                    }
                }
             if (!v.empty()){
                extList.push_back(v);
            }

        }
        return extList;
}
