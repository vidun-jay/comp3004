#ifndef ELEVATOR_H
#define ELEVATOR_H

class Elevator {
public:
    // Constructor
    Elevator();

    // getters/setters
    bool isObstructed() const;
    void setObstructed(bool value);
    int getCurrentFloor() const;
    void setCurrentFloor(int floor);

    // member functions
    void moveUp();
    void moveDown();


private:
    bool obstructed;
    int curr_floor;
};

#endif // ELEVATOR_H
