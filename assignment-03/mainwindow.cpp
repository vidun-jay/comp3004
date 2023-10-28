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

        // set the elevator buttons to checkable
        ui->one->setCheckable(true);
        ui->two->setCheckable(true);
        ui->three->setCheckable(true);
        ui->four->setCheckable(true);
        ui->five->setCheckable(true);
        ui->six->setCheckable(true);
}

MainWindow::~MainWindow() {
    delete ui;
}

Elevator elevator;

void MainWindow::reset_simulation() {
    // toggle simulation running indicator
    QPixmap simulation_running_pixmap(":/images/led-off.png");
    ui->led->setPixmap(simulation_running_pixmap.scaled(30, 30));

    // reset elevator properties
    elevator = Elevator();
}

void MainWindow::on_start_clicked() {

    // toggle simulation running indicator
    QPixmap simulation_running_pixmap(":/images/led-on.png");
    ui->led->setPixmap(simulation_running_pixmap.scaled(30, 30));

    // check if fire scenario is checked
    if (ui->fire_check->isChecked()) {
        QMessageBox::critical(this, "Unable to Start Elevator", "Please evacuate the elevator and building immediately and proceed to the nearest safe exit.");
        reset_simulation();
    }

    // check if the doors are obstructed
    if (ui->obstructed_check->isChecked()) {
        elevator.setObstructed(true);
        std::cout << elevator.isObstructed();
    } else if (!(ui->obstructed_check->isChecked())) {
        elevator.setObstructed(false);
    }

    // check if there is power
    if (ui->power_outage->isChecked()) {
        QMessageBox::information(this, "Power Failure", "The power is currently down and the elevatory is temporarily out of service. We apologize for the inconvenience.");
        reset_simulation();
    }

    // check if the cargo load is too high
    if ((ui->load->value() * 70) > 490) {
        QMessageBox::information(this, "Load Capacity Reached", "The elevator is currently at max capacity.");
    }
}


void MainWindow::on_close_door_button_clicked() {
    if (elevator.isObstructed()) {
        QMessageBox::critical(this, "Unable to Close Doors", "Elevator doors are obstructed. Please clear room for the doors to close and try again.");
        reset_simulation();
    }
}


void MainWindow::on_stop_clicked() {
    reset_simulation();
}

