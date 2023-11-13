#include "elevator.h"

// Constructor
Elevator::Elevator() : obstructed(false), curr_floor(1) { }

// Getters & Setters
bool Elevator::isObstructed() const { return obstructed; }
void Elevator::setObstructed(bool value) { obstructed = value; }
int Elevator::getCurrentFloor() const { return curr_floor; }

void Elevator::setCurrentFloor(int floor) {
    if (floor >= 0 && floor <= 6)
        curr_floor = floor;
}

// Member Functions
void Elevator::moveUp() {
    if (curr_floor < 6)
        curr_floor++;
}

void Elevator::moveDown() {
    if (curr_floor > 0) {
        curr_floor--;
    }
}
