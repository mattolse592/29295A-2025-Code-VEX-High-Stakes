#ifndef RINGDETECTOR_HPP
#define RINGDETECTOR_HPP

#include "Basic Control Classes/LimitSwitch.hpp"
#include "Basic Control Classes/OpticalSensor.hpp"

class RingDetector {
private:
    bool colourSort = true;
    bool allianceColourRed = true;

    OpticalSensor::RingType ring = OpticalSensor::RingType::None;

    bool touchingLimitSwitch = false;
    bool badColour = false;

    OpticalSensor OpticalSensor_;
    LimitSwitch LimSwitch_;

public:
    RingDetector() : OpticalSensor_(1), LimSwitch_('B') {
        OpticalSensor_.LEDon();
    }

    void Tick() {
        OpticalSensor_.Tick();
        LimSwitch_.Tick();

        if (!colourSort) return;

        if (LimSwitch_.GetValue()) {
            touchingLimitSwitch = true;
            ring = OpticalSensor_.GetRing(); //Not going to work because limit switch is still pressed when the ring moves off of optical snesor
        }
        else if (touchingLimitSwitch) {  // Rising edge of limit switch
            switch (ring)
            {
            case OpticalSensor::RingType::Red:
                badColour = !allianceColourRed;
                break;
            case OpticalSensor::RingType::Blue:
                badColour = allianceColourRed;
                break;
            default:
                break;
            }

            // do something here that makes hooks go backwards
            touchingLimitSwitch = false;
            ring = OpticalSensor::RingType::None;
        }
    }

    void SortOn() {
        colourSort = true;
        OpticalSensor_.LEDon();
    }
    void SortOff() {
        colourSort = false;
        OpticalSensor_.LEDoff();
    }
};

#endif  // RINGDETECTOR_HPP