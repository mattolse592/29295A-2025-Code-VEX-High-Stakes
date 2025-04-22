#ifndef DISTANCESENSOR_HPP
#define DISTANCESENSOR_HPP

#include "../include/pros/distance.hpp"

class DistanceSensor {
private:
    pros::Distance DistanceSensor_;
    int Distance_;

public:
    DistanceSensor(char PortNum) : DistanceSensor_{ PortNum } {}

    void Tick() {
        Distance_ = DistanceSensor_.get_distance();
    }

    int GetDistance() {
        return Distance_;
    }


};
#endif  // DISTANCESENSOR_HPP