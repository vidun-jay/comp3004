#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "elevator.h"
#include <iostream>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
        ui->setupUi(this);
        QPixmap simulation_running_pixmap(":/images/led-off.png");
        ui->led->setPixmap(simulation_running_pixmap.scaled(30, 30));
}

MainWindow::~MainWindow() {
    delete ui;
}

Elevator elevator;

void MainWindow::on_start_clicked() {

    // toggle simulation running indicator
    QPixmap simulation_running_pixmap(":/images/led-on.png");
    ui->led->setPixmap(simulation_running_pixmap.scaled(30, 30));

    if (ui->fire_check->isChecked()) {
        QMessageBox::critical(this, "Unable to Start Elevator", "Please evacuate the elevator and building immediately and proceed to the nearest safe exit.");
    } else if (ui->obstructed_check->isChecked()) {
        elevator.setObstructed(true);
        std::cout << elevator.isObstructed();
    } else if (!(ui->obstructed_check->isChecked())) {
        elevator.setObstructed(false);
        std::cout << elevator.isObstructed();
    }
}


void MainWindow::on_close_door_button_clicked() {
    if (elevator.isObstructed()) {
        QMessageBox::critical(this, "Unable to Close Doors", "Elevator doors are obstructed. Please clear room for the doors to close and try again.");
    }
}


void MainWindow::on_stop_clicked() {

    // toggle simulation running indicator
    QPixmap simulation_running_pixmap(":/images/led-off.png");
    ui->led->setPixmap(simulation_running_pixmap.scaled(30, 30));

    // reset elevator properties
    elevator = Elevator();

}

