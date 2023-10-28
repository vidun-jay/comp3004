#ifndef ELEVATOR_H
#define ELEVATOR_H

class Elevator {
private:
    int current_floor;
    std::string direction;
    std::string state;
    int max_capacity;
    int current_load;

public:
    void moveUp();
    void moveDown();
    void openDoor();
    void closeDoor();
    void displayMessage();
    void ringBell();
};

#endif