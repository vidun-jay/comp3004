#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "elevator.h"
#include <iostream>
#include <QPixmap>
#include <unistd.h>

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

        // don't show elevator control panel until settings are set
        ui->elevator_panel->hide();
        ui->request_elevator->hide();
}

MainWindow::~MainWindow() {
    delete ui;
}

Elevator elevator;

void MainWindow::reset_simulation() {

    ui->elevator_panel->hide(); // hide the elevator panel
    ui->request_elevator->hide(); // hide the request elevator button
    ui->display->display(1); // reset display to 0

    // toggle simulation running indicator
    QPixmap simulation_running_pixmap(":/images/led-off.png");
    ui->led->setPixmap(simulation_running_pixmap.scaled(30, 30));

    // reset elevator properties
    elevator = Elevator();
}

void MainWindow::moveToFloor(int target) {

    // check to see if the doors can close before moving
    if (elevator.isObstructed()) {
        QMessageBox::critical(this, "Unable to Close Doors", "Elevator doors are obstructed. Please clear room for the doors to close and try again.");
        reset_simulation();
    } else {
        while (elevator.getCurrentFloor() != target) {
            if (elevator.getCurrentFloor() < target) {
                sleep(1);
                elevator.moveUp();
                ui->display->display(elevator.getCurrentFloor());
                QCoreApplication::processEvents();

            } else {
                // TODO: figure out a way to not hold entire UI hostage
                sleep(1);
                elevator.moveDown();
                ui->display->display(elevator.getCurrentFloor());
                QCoreApplication::processEvents();
            }
        }
    }
}

void MainWindow::on_start_clicked() {

    ui->request_elevator->show();
    // set the current floor in the elevator to the one from simulation settings
    elevator.setCurrentFloor(ui->curr_floor->value());
    ui->display->display((elevator.getCurrentFloor()));

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
        reset_simulation();
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


void MainWindow::on_six_clicked() {

    // update the display
    moveToFloor(6);

    // once floor is reached, un-press the button
    ui->six->setChecked(false);
    sleep(2); // wait for passenger to get off
}


void MainWindow::on_five_clicked() {

    // update the display
    moveToFloor(5);

    // once floor is reached, un-press the button
    ui->five->setChecked(false);
    sleep(2); // wait for passenger to get off

}


void MainWindow::on_four_clicked() {

    // update the display
    moveToFloor(4);

    // once floor is reached, un-press the button
    ui->four->setChecked(false);
    sleep(2); // wait for passenger to get off

}


void MainWindow::on_three_clicked() {

    // update the display
    moveToFloor(3);

    // once floor is reached, un-press the button
    ui->three->setChecked(false);
    sleep(2); // wait for passenger to get offs

}


void MainWindow::on_two_clicked() {

    // update the display
    moveToFloor(2);

    // once floor is reached, un-press the button
    ui->two->setChecked(false);
    sleep(2); // wait for passenger to get offs

}


void MainWindow::on_one_clicked() {

    // update the display
    moveToFloor(1);

    // once floor is reached, un-press the button
    ui->one->setChecked(false);

}

void MainWindow::on_help_clicked() {
    QMessageBox::information(this, "Assistance Requested", "The staff have been notified that you require assistance. Starting voice line...");
}

void MainWindow::on_request_elevator_clicked() {
    // show elevator panel
    sleep(3);
    ui->elevator_panel->show();
}

