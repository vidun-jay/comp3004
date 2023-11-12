#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "elevator.h"
#include <iostream>
#include <QPixmap>
#include <unistd.h>
#include <functional>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
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
        ui->one_2->setCheckable(true);
        ui->two_2->setCheckable(true);
        ui->three_2->setCheckable(true);
        ui->four_2->setCheckable(true);
        ui->five_2->setCheckable(true);
        ui->six_2->setCheckable(true);

        // don't show elevator control panels until settings are set
        ui->elevator_panel->hide();
        ui->request_elevator->hide();
        ui->elevator_panel_2->hide();
        ui->request_elevator_2->hide();

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::reset_simulation() {

    ui->elevator_panel->hide(); // hide the elevator panel
    ui->elevator_panel_2->hide(); // hide the second elevator panel
    ui->request_elevator->hide(); // hide the request elevator button
    // reset displays to 1
    ui->display->display(1);
    ui->display_2->display(1);

    // toggle simulation running indicator
    QPixmap simulation_running_pixmap(":/images/led-off.png");
    ui->led->setPixmap(simulation_running_pixmap.scaled(30, 30));

    // reset elevator properties
    elevator = Elevator();
    elevator2 = Elevator();
}

void MainWindow::moveToFloor(int target, Elevator& e, int id) {

    // print to console
    std::cout << "[CONSOLE] User selected floor " << target << " on elevator " << id << std::endl;

    // check to see if the doors can close before moving
    if (e.isObstructed()) {
        QMessageBox::critical(this, "Unable to Close Doors", "Elevator doors are obstructed. Please clear room for the doors to close and try again.");
        reset_simulation();
    } else {
        while (e.getCurrentFloor() != target) {
            if (e.getCurrentFloor() < target) {
                sleep(1);
                e.moveUp();
            } else {
                sleep(1);
                e.moveDown();
            }
            if (id == 1)
                ui->display->display(e.getCurrentFloor());
           else if (id == 2)
                ui->display_2->display(e.getCurrentFloor());
            QCoreApplication::processEvents();
        }
    }
}

void MainWindow::on_start_clicked() {

    ui->request_elevator->show();
    ui->request_elevator_2->show();
    // set the current floor in the elevator to the one from simulation settings
    elevator.setCurrentFloor(ui->curr_floor->value());
    elevator2.setCurrentFloor(ui->curr_floor->value());
    ui->display->display((elevator.getCurrentFloor()));
    ui->display_2->display((elevator.getCurrentFloor()));

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
        elevator2.setObstructed(true);
        std::cout << elevator.isObstructed();
    } else if (!(ui->obstructed_check->isChecked())) {
        elevator.setObstructed(false);
        elevator2.setObstructed(false);
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

void MainWindow::on_close_door_button_2_clicked() {
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
    moveToFloor(6, elevator, 1);

    // once floor is reached, un-press the button
    ui->six->setChecked(false);
    std::cout << "[CONSOLE] Elevator 1 has arrived at floor 6" << std::endl;
    sleep(2); // wait for passenger to get off
}


void MainWindow::on_five_clicked() {

    // update the display
    moveToFloor(5, elevator, 1);

    // once floor is reached, un-press the button
    ui->five->setChecked(false);
    std::cout << "[CONSOLE] Elevator 1 has arrived at floor 5" << std::endl;
    sleep(2); // wait for passenger to get off
}


void MainWindow::on_four_clicked() {

    // update the display
    moveToFloor(4, elevator, 1);

    // once floor is reached, un-press the button
    ui->four->setChecked(false);
    std::cout << "[CONSOLE] Elevator 1 has arrived at floor 4" << std::endl;
    sleep(2); // wait for passenger to get off

}


void MainWindow::on_three_clicked() {

    // update the display
    moveToFloor(3, elevator, 1);

    // once floor is reached, un-press the button
    ui->three->setChecked(false);
    std::cout << "[CONSOLE] Elevator 1 has arrived at floor 3" << std::endl;
    sleep(2); // wait for passenger to get offs

}


void MainWindow::on_two_clicked() {

    // update the display
    moveToFloor(2, elevator, 1);

    // once floor is reached, un-press the button
    ui->two->setChecked(false);
    std::cout << "[CONSOLE] Elevator 1 has arrived at floor 2" << std::endl;
    sleep(2); // wait for passenger to get offs

}


void MainWindow::on_one_clicked() {

    // update the display
    moveToFloor(1, elevator, 1);

    // once floor is reached, un-press the button
    ui->one->setChecked(false);
    std::cout << "[CONSOLE] Elevator 1 has arrived at floor 1" << std::endl;
    sleep(2);
}

void MainWindow::on_six_2_clicked() {

    // update the display
    moveToFloor(6, elevator2, 2);

    // once floor is reached, un-press the button
    ui->six_2->setChecked(false);
    std::cout << "[CONSOLE] Elevator 2 has arrived at floor 6" << std::endl;
    sleep(2); // wait for passenger to get off
}


void MainWindow::on_five_2_clicked() {

    // update the display
    moveToFloor(5, elevator2, 2);

    // once floor is reached, un-press the button
    ui->five_2->setChecked(false);
    std::cout << "[CONSOLE] Elevator 2 has arrived at floor 5" << std::endl;
    sleep(2); // wait for passenger to get off

}


void MainWindow::on_four_2_clicked() {

    // update the display
    moveToFloor(4, elevator2, 2);

    // once floor is reached, un-press the button
    ui->four_2->setChecked(false);
    std::cout << "[CONSOLE] Elevator 2 has arrived at floor 4" << std::endl;
    sleep(2); // wait for passenger to get off

}


void MainWindow::on_three_2_clicked() {

    // update the display
    moveToFloor(3, elevator2, 2);

    // once floor is reached, un-press the button
    ui->three_2->setChecked(false);
    std::cout << "[CONSOLE] Elevator 2 has arrived at floor 3" << std::endl;
    sleep(2); // wait for passenger to get offs

}


void MainWindow::on_two_2_clicked() {

    // update the display
    moveToFloor(2, elevator2, 2);

    // once floor is reached, un-press the button
    ui->two_2->setChecked(false);
    std::cout << "[CONSOLE] Elevator 2 has arrived at floor 2" << std::endl;
    sleep(2); // wait for passenger to get offs

}


void MainWindow::on_one_2_clicked() {

    // update the display
    moveToFloor(1, elevator2, 2);

    // once floor is reached, un-press the button
    ui->one_2->setChecked(false);
    std::cout << "[CONSOLE] Elevator 2 has arrived at floor 1" << std::endl;
    sleep(2);
}

void MainWindow::on_help_clicked() {
    QMessageBox::information(this, "Assistance Requested", "The staff have been notified that you require assistance. Starting voice line...");
}

void MainWindow::on_request_elevator_clicked() {
    std::cout << "[CONSOLE] Elevator 1 requested" << std::endl;
    // show elevator panel
    sleep(2);
    ui->elevator_panel->show();
    std::cout << "[CONSOLE] Elevator 1 has arrived" << std::endl;
}

void MainWindow::on_request_elevator_2_clicked() {
    std::cout << "[CONSOLE] Elevator 2 requested" << std::endl;
    // show elevator panel
    sleep(2);
    ui->elevator_panel_2->show();
    std::cout << "[CONSOLE] Elevator 2 has arrived" << std::endl;
}


