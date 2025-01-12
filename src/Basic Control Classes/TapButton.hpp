#ifndef TAPBUTTON_HPP
#define TAPBUTTON_HPP

#include "../include/pros/misc.hpp"
#include "../include/EZ-Template/util.hpp"

class TapButton
{

private:
    pros::Controller& Master_;
    pros::controller_digital_e_t Button_;

    int Pressed_ = 0;
public:
    TapButton(pros::controller_digital_e_t button, pros::Controller Master = master)
        : Master_(Master)
    {
        Button_ = button;
    }

    void Tick()
    {
        Pressed_ = Pressed_ + 1;
    }

    int TimesPressed()
    {
        return Pressed_;
    }
};
#endif // TAPBUTTON_HPP