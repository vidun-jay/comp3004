#ifndef GUI_H
#define GUI_H

class GUI {
private:
    std::string displayText;

public:
    void updateDisplay(const Elevator& elevator);
    void showWarning(const std::string& message);
};

#endif