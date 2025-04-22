#ifndef RINGDETECTOR2_HPP
#define RINGDETECTOR2_HPP

#include "Basic Control Classes/DistanceSensor.hpp"
#include "Basic Control Classes/OpticalSensor.hpp"

class RingDetector2 {
private:
    bool colourSort = true;
    bool allianceColourRed;

    OpticalSensor::RingType ring = OpticalSensor::RingType::None;

    bool badColour = false;

    int reverseTimer = 0;

    OpticalSensor OpticalSensor_;
    DistanceSensor DistanceSensor_;
    

public:
    RingDetector2() : OpticalSensor_(19), DistanceSensor_(17) {
        SortOn();
    }

    void Tick() {
        OpticalSensor_.Tick();
        DistanceSensor_.Tick();

        if (!colourSort) return;

        if (DistanceSensor_.GetDistance() < 10 && reverseTimer < 0) {
            ring = OpticalSensor_.GetRing();
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
                reverseTimer = 23;
            }
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

#endif  // RINGDETECTOR2_HPP