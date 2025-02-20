#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "Basic Control Classes/Motor.hpp"
#include "RingDetector.hpp"

class Intake
{

private:
    Motor Preroller_;
    Motor Hooks_;

    RingDetector RingDetector_;

    int PreRollerSpeed_;
    int HooksSpeed_;

public:
    Intake(Motor Preroller, Motor Hooks)
        : Preroller_(Preroller), Hooks_(Hooks)
    {
    }

    void InputTick() {
        RingDetector_.Tick();
    }

    void OutputTick() {
        Preroller_.SetSpeed(PreRollerSpeed_);
        Hooks_.SetSpeed(HooksSpeed_);

        if (RingDetector_.GetReverseTimer() > 0 || Hooks_.GetReverseTimer() > 0) {
            Hooks_.SetSpeed(127);
        }
    }

    void Forward()
    {
        PreRollerSpeed_ = 127;
        HooksSpeed_ = -127;
    }

    void Reverse()
    {
        PreRollerSpeed_ = -127;
        HooksSpeed_ = 127;
    }

    void Stop()
    {
        PreRollerSpeed_ = 0;
        HooksSpeed_ = 0;
    }

    void ChangePreRollerSpeed(int speed)
    {
        PreRollerSpeed_ = speed;
    }

    void ChangeHooksSpeed(int speed)
    {
        HooksSpeed_ = speed;
    }

    void SortOn() {
        RingDetector_.SortOn();
    }

    void SortOff() {
        RingDetector_.SortOff();
    }

    void SetAllianceAsRed(bool isRed) {
        RingDetector_.SetAllianceAsRed(isRed);
    }

};
#endif // INTAKE_HPP