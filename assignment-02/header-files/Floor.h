#ifndef FLOOR_H
#define FLOOR_H

class Floor {
private:
    int floor_number;
    bool up_button_pressed;
    bool down_button_pressed;

public:
    void pressUpButton();
    void pressDownButton();
};

#endif