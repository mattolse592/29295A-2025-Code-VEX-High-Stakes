#ifndef LINETRACKER_HPP
#define LINETRACKER_HPP

#include "../include/pros/adi.hpp"

class LineTracker {
private:
    pros::ADIDigitalIn LineTracker_;
    int Value_;

public:
    LineTracker(char PortName) : LineTracker_{ PortName } {}

    void Tick() {
        Value_ = LineTracker_.get_value();
    }

    int GetValue() {
        return Value_;
    }


};
#endif  // LINETRACKER_HPP