#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filereader.h"
#include "graph.h"
#include "QInputDialog"

FileReader fl;
Graph g;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("Wczytaj plik");
    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(handleButton()));
    ui->pushButton_2->setText("Wczytaj liczbę");
    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(inputText()));
    ui->pushButton_3->setText("Stworz graf");
    connect(ui->pushButton_3, SIGNAL(clicked()),this, SLOT(colorGraph()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{

    QTextStream out(stdout);
    fl.chooseFile();

   // for (std::list<std::string>::iterator it = myList.begin(); it!=myList.end();++it){
   // std::cout << *it << endl;
  //  }

}

void MainWindow::inputText()
{
    bool ok;
    varU = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
                                 tr("Podaj liczbę:"), 25, 0, 100, 1, &ok);

  //  if (ok)
      //  integerLabel->setText(tr("%1%").arg(varU));
}

int MainWindow::getU(){
    return varU;
}

void MainWindow::colorGraph()
{
    /*Graph g1(4);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);


    cout << "Coloring of Graph 1 \n";
    g1.greedyColoring();*/

    /*Graph gr(varU);

    gr.createGraph(fl.getList(), varU);*/

    QVector<QVector<QString>> extList = fl.createNodes(fl.getList());
    int index = 1;
    int key = 0;
    int input = fl.getInput();
    int output = fl.getOutput();
    int u = varU;

    for (QVector<QVector<QString>>::iterator it = extList.begin(); it != extList.end(); ++it){

        count = count + it->count();

    }
    std::cout << "varU: " << varU << endl;
    std::cout << "input: " << input << endl;
    std::cout << "output: " << output << endl;
    std::cout << "node count: " << count << endl;
    g.setV(count);

    for(QVector<QVector<QString>>::iterator it = extList.begin(); it != extList.end()-1; ++it) {
             int x = it->size();
        for(QVector<QString>::iterator itt = it->begin(); itt != it->end(); ++itt) {

             int key1 = key + x;
             std::cout << key << " : "<< itt->toStdString()<<endl;

             for(QVector<QVector<QString>>::iterator ittt = extList.begin()+index; ittt != extList.end(); ++ittt) {
                 for(QVector<QString>::iterator itttt = ittt->begin(); itttt != ittt->end(); ++itttt) {
                      std::cout << key1 << " : " << itttt->toStdString()<<endl;
                      if (itt->mid(0,input-u)==itttt->mid(0,input-u)&&itt->mid(input,input+output)!=itttt->mid(input,input+output)){
                          g.addEdge(key,key1);

                          cout << "krawedz pomiedzy nodem " << key << " a nodem " << key1 << endl;
                      }else {

                      } key1++;
                 }
             } key++; x--;
        }
    index++;
    }
    /*cout << "start LFRColoring" << endl;
    g.LFRColoring();
    cout << "start LFRBitColoring" << endl;
    g.LFRBitColoring();
    cout << "start EqualBitColoring" << endl;
    g.EqualBitColoring();*/
}
