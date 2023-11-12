#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "elevator.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_clicked();
    void on_close_door_button_clicked();
    void on_stop_clicked();

    void on_six_clicked();
    void on_five_clicked();
    void on_four_clicked();
    void on_three_clicked();
    void on_two_clicked();
    void on_one_clicked();

    void on_six_2_clicked();
    void on_five_2_clicked();
    void on_four_2_clicked();
    void on_three_2_clicked();
    void on_two_2_clicked();
    void on_one_2_clicked();

    void on_help_clicked();

    void on_request_elevator_clicked();

    void on_request_elevator_2_clicked();

    void on_close_door_button_2_clicked();

private:
    Ui::MainWindow *ui;
    void reset_simulation();
    void moveToFloor(int target, Elevator& e, int eid);
    Elevator elevator;
    Elevator elevator2;
};
#endif // MAINWINDOW_H
