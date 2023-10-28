#include "elevator.h"

// Constructor
Elevator::Elevator() : obstructed(false) { }

// function to return whether or not elevator doors are obstructed
bool Elevator::isObstructed() const { return obstructed; }

// setter for obstructed
void Elevator::setObstructed(bool value) { obstructed = value; }
