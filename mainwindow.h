#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int getU();

private:
    Ui::MainWindow *ui;
    int varU;
    int count;

private slots:
    void handleButton();
    void inputText();
    void createGraph();
    void LFRGraph();
    void LFRBitGraph();
    void EqualBitGraph();
    void addNode();
    void addEdge();
    void MISGraph();
    void MISBitGraph();
    void printGraph();
};

#endif // MAINWINDOW_H
