#ifndef PISTON_HPP
#define PISTON_HPP

#include "../../include/pros/adi.hpp"

class Pistonf {
private:
    pros::ADIDigitalOut Port_;
    bool State_;

public:
    Pistonf(char PortName)
        : Port_(PortName), State_(false) {
    }

    void Tick() {
    }

    void Activate() {
        Port_.set_value(true);
    }

    void Deactivate() {
        Port_.set_value(false);
    }

    void SetValue(bool value) {
        Port_.set_value(value);
    }
};
#endif  // PISTON_HPP