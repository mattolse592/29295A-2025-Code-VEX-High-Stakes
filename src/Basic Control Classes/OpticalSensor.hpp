#ifndef OPTICALSENSOR_HPP
#define OPTICALSENSOR_HPP

#include "../include/pros/optical.hpp"

class OpticalSensor {
private:
    pros::Optical OpticalSensor_;
    int Hue_;
    int Proximity_;

    const int MIN_RING_DISTANCE = 150;

public:
    OpticalSensor(char PortNum) : OpticalSensor_{ PortNum } {}

    enum RingType { None, Red, Blue };

    void Tick() {
        Proximity_ = OpticalSensor_.get_proximity();
        Hue_ = OpticalSensor_.get_hue();
    }

    RingType GetRing() {
        if (Proximity_ <= MIN_RING_DISTANCE) return RingType::None;
        if (Hue_ >= 180 && Hue_ <= 245) return RingType::Blue;
        if (Hue_ >= 340 || Hue_ <= 20) return RingType::Red;
        return RingType::None;
    }

    void LEDon() {
        OpticalSensor_.set_led_pwm(100);
    }

    void LEDoff() {
        OpticalSensor_.set_led_pwm(0);
    }
};
#endif  // OPTICALSENSOR_HPP