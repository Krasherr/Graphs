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
    connect(ui->pushButton_3, SIGNAL(clicked()),this, SLOT(createGraph()));
    ui->pushButton_4->setText("Kolorowanie grafu LFR");
    connect(ui->pushButton_4, SIGNAL(clicked()),this, SLOT(LFRGraph()));
    ui->pushButton_5->setText("Kolorowanie grafu LFR Bit");
    connect(ui->pushButton_5, SIGNAL(clicked()),this, SLOT(LFRBitGraph()));
    ui->pushButton_6->setText("Kolorowanie grafu Equal Bit");
    connect(ui->pushButton_6, SIGNAL(clicked()),this, SLOT(EqualBitGraph()));
    ui->pushButton_7->setText("Dodaj wezel");
    connect(ui->pushButton_7, SIGNAL(clicked()),this, SLOT(addNode()));
    ui->pushButton_8->setText("Dodaj krawedz");
    connect(ui->pushButton_8, SIGNAL(clicked()),this, SLOT(addEdge()));
    ui->pushButton_9->setText("Kolorowanie grafu MIS");
    connect(ui->pushButton_9, SIGNAL(clicked()),this, SLOT(MISGraph()));
    ui->pushButton_10->setText("Kolorowanie grafu MIS Bit");
    connect(ui->pushButton_10, SIGNAL(clicked()),this, SLOT(MISBitGraph()));
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
    int max = fl.getInput();
    varU = QInputDialog::getInt(this, tr("QInputDialog::getInteger()"),
                                tr("Podaj liczbę:"), 0, 0, 100, 1, &ok);
}

int MainWindow::getU()
{
    return varU;
}

void MainWindow::createGraph()
{

    QVector<QVector<QString>> extList = fl.createNodes(fl.getList());
    int index = 1;
    int key = 0;
    int input = fl.getInput();
    int output = fl.getOutput();
    int u = varU;
    int v = input - u;
    for (QVector<QVector<QString>>::iterator it = extList.begin(); it != extList.end(); ++it) {
        for(QVector<QString>::iterator itt = it->begin(); itt != it->end(); ++itt) {
            cout << itt->toStdString()<<endl;
        }
        count = count + it->count();

    }

    g.setV(count);

    for(QVector<QVector<QString>>::iterator it = extList.begin(); it != extList.end()-1; ++it) {
        int x = it->size();    //Sprawdzenie ile linii jest w danym rozwinietym wezle.
        for(QVector<QString>::iterator itt = it->begin(); itt != it->end(); ++itt) {

            int key1 = key + x;
            std::cout << key << " : "<< itt->toStdString()<<endl;

            for(QVector<QVector<QString>>::iterator ittt = extList.begin()+index; ittt != extList.end(); ++ittt) {
                for(QVector<QString>::iterator itttt = ittt->begin(); itttt != ittt->end(); ++itttt) {

                    std::cout << key1 << " : " << itttt->toStdString()<<endl;
                    int xwe = 0;
                    for (int i=1;i<=v;++i){
                        if (itt->mid(i-1,1)!=itttt->mid(i-1,1)&&itt->mid(i-1,1)!="-"&&itttt->mid(i-1,1)!="-"){
                            key1++;
                            break;

                        } else if (i==v){

                            int f=0;
                            for (int j=1; j<=output; ++j){
                                if (itt->mid(input+j-1,1)==itttt->mid(input+j-1,1)||itt->mid(input+j-1,1)=="-"||itttt->mid(input+j-1,1)=="-"){
                                    f++;
                                }

                            }
                            if (f!=output) {
                                g.addEdge(key,key1);
                                key1++;
                                cout << "krawedz pomiedzy nodem " << key << " a nodem " << key1 << endl;
                            }  else {
                                key1++;
                        }

                        }
                    }
                }
            }
            key++;
            x--;
        }
        index++;
    }


    for (int i = 0; i < count; i++) {
        ui->comboBox->addItem(QString::number(i));
        ui->comboBox_2->addItem(QString::number(i));
    }
}

void MainWindow::LFRGraph()
{
    g.LFRColoring();
}

void MainWindow::LFRBitGraph()
{
    g.LFRBitColoring();
}

void MainWindow::EqualBitGraph()
{
    g.EqualBitColoring();
}

void MainWindow::MISGraph()
{
    g.MISColoring();
}

void MainWindow::MISBitGraph()
{
    g.MISBitColoring();
}

void MainWindow::addNode()
{
    g.addNode();
    ui->comboBox->addItem(QString::number(g.getV()-1));
    ui->comboBox_2->addItem(QString::number(g.getV()-1));
}

void MainWindow::addEdge()
{

    int node1 = ui->comboBox->currentText().toInt();
    int node2 = ui->comboBox_2->currentText().toInt();

    if (node1 > node2) {
        g.addEdge(node1, node2);
    } else if (node2 > node1) {
        g.addEdge(node2, node1);
    } else {
        QMessageBox msgBox;
        msgBox.setText("Nie mozesz polaczyc tych samych wezlow!");
        msgBox.exec();
    }
}

void MainWindow::printGraph()
{
    g.printGraph();
}
