#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "calculator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto *calc = new Calculator(this);
    setCentralWidget(calc);
}

MainWindow::~MainWindow()
{
    delete ui;
}
