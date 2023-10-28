#ifndef PASSENGER_H
#define PASSENGER_H

class Passenger {
private:
    int current_floor;
    int desired_floor;

public:
    void requestElevator();
    void selectFloor(int floor);
    void enterElevator();
    void exitElevator();
    void getAssistance();
};

#endif