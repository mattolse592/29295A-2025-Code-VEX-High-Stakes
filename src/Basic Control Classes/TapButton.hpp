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
    bool dePressed_;
public:
    TapButton(pros::controller_digital_e_t button, pros::Controller Master = master)
        : Master_(Master)
    {
        Button_ = button;
    }

    void Tick()
    {
        if (Master_.get_digital_new_press(Button_))
        {
            Pressed_ = Pressed_ + 1;
        }
        dePressed_ = Master_.get_digital(Button_);
        
    }

    int TimesPressed()
    {
        return Pressed_;
    }
     bool IsPressed()
    {
        return dePressed_;
    }
};
#endif // TAPBUTTON_HPP