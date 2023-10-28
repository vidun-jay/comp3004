#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
private:
    std::string type;

public:
    void triggerAlarm();
    int getCurrentFloor();
    void updateDisplay();
    int getCurrentLoad();
    void maxCapacityAlarm();
    void emergencyProcedure();
};

#endif