#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filereader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("Wczytaj plik");
    connect(ui->pushButton, SIGNAL(clicked()),this, SLOT(handleButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButton()
{
    FileReader fl;
    fl.chooseFile();
}
