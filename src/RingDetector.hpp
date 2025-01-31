#ifndef RINGDETECTOR_HPP
#define RINGDETECTOR_HPP

#include "Basic Control Classes/LimitSwitch.hpp"
#include "Basic Control Classes/OpticalSensor.hpp"

class RingDetector {
private:
    bool colourSort = true;
    bool allianceColourRed;

    OpticalSensor::RingType ring = OpticalSensor::RingType::None;

    bool touchingLimitSwitch = false;
    bool badColour = false;

    int reverseTimer = 0;

    OpticalSensor OpticalSensor_;
    LimitSwitch LimSwitch_;

public:
    RingDetector() : OpticalSensor_(19), LimSwitch_('B') {
        SortOn();
    }

    void Tick() {
        OpticalSensor_.Tick();
        LimSwitch_.Tick();

        if (!colourSort) return;

        if (LimSwitch_.GetValue()) {
            ring = OpticalSensor_.GetRing();
            touchingLimitSwitch = true;
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
                badColour = false;
                break;
            }

            if (badColour) {
                reverseTimer = 20;
            }
            touchingLimitSwitch = false;
            ring = OpticalSensor::RingType::None;
        }

        reverseTimer--;
    }

    void SortOn() {
        colourSort = true;
        OpticalSensor_.LEDon();
    }
    void SortOff() {
        colourSort = false;
        OpticalSensor_.LEDoff();
    }

    int GetReverseTimer() {
        return reverseTimer;
    }

    void SetAllianceAsRed(bool isRed) {
        allianceColourRed = isRed;
    }
};

#endif  // RINGDETECTOR_HPP