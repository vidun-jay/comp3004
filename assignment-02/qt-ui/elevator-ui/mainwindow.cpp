#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::E)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

