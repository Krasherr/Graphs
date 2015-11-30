#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filereader.h"
#include "QInputDialog"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("Wczytaj plik");
    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(handleButton()));
    ui->pushButton_2->setText("Wczytaj liczbę");
    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(inputText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{
    FileReader fl;
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
