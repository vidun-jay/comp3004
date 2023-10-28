#ifndef ELEVATOR_H
#define ELEVATOR_H

class Elevator {
public:
    // Constructor
    Elevator();

    // getters/setters
    bool isObstructed() const;
    void setObstructed(bool value);

private:
    bool obstructed;
};

#endif // ELEVATOR_H
