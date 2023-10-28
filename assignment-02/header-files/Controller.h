#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include "Elevator.h"
#include "Floor.h"

class Controller {
private:
    std::vector<Elevator> elevators;
    std::vector<Floor> floors;

public:
    void assignElevator();
};

#endif